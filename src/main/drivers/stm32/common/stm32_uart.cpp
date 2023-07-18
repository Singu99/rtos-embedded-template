
#include "drivers/platform.hpp"
#include "drivers/stm32/common/stm32_uart.hpp"
#include "drivers/pal/uart.hpp"
#include "stm32_uart_impl.hpp"
#include "drivers/common/hardware.hpp"
#include "stm32_uart.hpp"
#include "config.hpp"
#include "drivers/rcc.h"



// Private function declarations
static void configure_uart_pin(GPIO_TypeDef* port_reg, uint32_t pin, uint32_t af);
static void configure_uart_pin(pal::uart::id dev_id, pal::gpio pin, const pal::stm32::gpio_stm32* hw_gpios, uint32_t rcc);

/* gpio init function declarations */
static void initClockPortA();
static void initClockPortB();
static void initClockPortC();
static void initClockPortD();
static void initClockPortE();
static void initClockPortF();
static void initClockPortG();
static void initClockPortH();
static void initClockPortI();
static void initClockPortJ();
static void initClockPortK();

/* Module tables */
static std::array<pal::uart_interruptable*, 9> uart_interruptable_table = { 
    pal::uart_interruptable::null_interrupt(),
    pal::uart_interruptable::null_interrupt(),
    pal::uart_interruptable::null_interrupt(),
    pal::uart_interruptable::null_interrupt(),
    pal::uart_interruptable::null_interrupt(),
    pal::uart_interruptable::null_interrupt(),
    pal::uart_interruptable::null_interrupt(),
    pal::uart_interruptable::null_interrupt(),
    pal::uart_interruptable::null_interrupt()
 };

static std::array<uint32_t, 3> mode_table = { 
    UART_MODE_TX,
    UART_MODE_RX,
    UART_MODE_TX_RX,
};

/* gpio clock table */
static std::array<void(*)(), 11> gpio_clock_table = {
    initClockPortA,
    initClockPortB,
    initClockPortC,
    initClockPortD,
    initClockPortE,
    initClockPortF,
    initClockPortG,
    initClockPortH,
    initClockPortI,
    initClockPortJ,
    initClockPortK
};

uart_device_stm32::uart_device_stm32(pal::uart::id dev_id)
    : pal::uart_device(dev_id), m_handle()
{
    init_handle();
}

// TODO: Add more function calls like old driver
pal::uart::status uart_device_stm32::open(pal::uart::bus_comm com, pal::uart::mode mode, uint32_t baudrate, pal::uart_interruptable* rsi)
{
    // Retreive hardware
    std::optional<const pal::stm32::uart::hw_t*> hw = hardware<pal::stm32::uart::hw_t>::get(m_dev_id);
    
    if (!hw.has_value())    return pal::uart::status::not_supported;
    
    const auto uartHardware = hw.value();

    // Init uart structure
    m_handle.Init.BaudRate = baudrate;
    m_handle.Init.Mode = mode_table[static_cast<uint32_t>(mode)];

    switch (com)
    {
    case pal::uart::bus_comm::full_duplex:
        configure_uart_pin(m_dev_id, config::rx::get_uart_rx_pin(m_dev_id), uartHardware->rxPins, uartHardware->rcc);
        configure_uart_pin(m_dev_id, config::rx::get_uart_tx_pin(m_dev_id), uartHardware->txPins, uartHardware->rcc);
        HAL_UART_Init(&m_handle);
        break;
    case pal::uart::bus_comm::half_duplex:
        configure_uart_pin(m_dev_id, config::rx::get_uart_tx_pin(m_dev_id), uartHardware->txPins, uartHardware->rcc);
        HAL_HalfDuplex_Init(&m_handle);
        break;
    default:
        return pal::uart::status::not_supported;
        break;
    }

    // Init interrupt case
    if (rsi != nullptr)
    {
        std::optional<const pal::stm32::uart::hw_t*> hw = hardware<pal::stm32::uart::hw_t>::get(m_dev_id);
        if (hw.has_value())
        {
            const auto uartHardware = hw.value();
            m_rsi = rsi;
            HAL_NVIC_SetPriority(uartHardware->rxIrq, 0, 0);
            HAL_NVIC_EnableIRQ(uartHardware->rxIrq);
            uart_interruptable_table[static_cast<uint32_t>(m_dev_id)] = rsi;
        }
    }
    return pal::uart::status::ok;
}

void uart_device_stm32::close()
{
    // Hal deinit uart
}


pal::uart::status uart_device_stm32::send(void *buffer, uint32_t size)
{

    return pal::uart::status::ok;
}

pal::uart::status uart_device_stm32::send_nonblocking(void *buffer, uint32_t size, bool recursive)
{
    return pal::uart::status::ok;
}

pal::uart::status uart_device_stm32::receive(void *buffer, uint32_t size)
{
    return pal::uart::status::ok;
}

pal::uart::status uart_device_stm32::receive_nonblocking(void *buffer, uint32_t size, bool recursive)
{
    return pal::uart::status::ok;
}

void uart_device_stm32::init_handle()
{
    std::optional<const pal::stm32::uart::hw_t*> hw = hardware<pal::stm32::uart::hw_t>::get(m_dev_id);
    if (hw.has_value())
    {
        const auto uartHardware = hw.value();
        m_handle.Instance = uartHardware->reg;
        m_handle.Init.BaudRate = 0;
        m_handle.Init.WordLength = UART_WORDLENGTH_8B;
        m_handle.Init.StopBits = UART_STOPBITS_1;
        m_handle.Init.Parity = UART_PARITY_NONE;
        m_handle.Init.Mode = UART_MODE_TX_RX;       // Default for now
    }
}

// ***** Private functions *****
static void configure_uart_pin(pal::uart::id dev_id, pal::gpio pin, const pal::stm32::gpio_stm32* hw_gpios, uint32_t rcc)
{
    // Enable the port gpio clock
    gpio_clock_table[static_cast<uint32_t>(pin.m_port)]();

    // Enable uart bus clock
    RCC_ClockCmd(rcc, ENABLE);
    
    // Check if the pin is in the rx pins
    for (int i = 0; i < UART_MAX_PINS; i++)
    {
        if (hw_gpios[i].gpio == pin)
        {
            configure_uart_pin(hw_gpios[i].port, 
                hw_gpios[i].pin, 
                hw_gpios[i].af);
            return;
        }
    }
}

static void configure_uart_pin(GPIO_TypeDef* port_reg, uint32_t pin, uint32_t af)
{
    // Enable the clock
    GPIO_InitTypeDef GPIO_InitStruct = {};
    GPIO_InitStruct.Pin = pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = af;
    HAL_GPIO_Init(port_reg, &GPIO_InitStruct);
}

/* Should be in gpio */
#ifdef GPIOA
    static void initClockPortA() { __HAL_RCC_GPIOA_CLK_ENABLE();}
#else
    static void initClockPortA() {}
#endif
#ifdef GPIOB
    static void initClockPortB() { __HAL_RCC_GPIOB_CLK_ENABLE();}
#else
    static void initClockPortB() {}
#endif
#ifdef GPIOC
    static void initClockPortC() { __HAL_RCC_GPIOC_CLK_ENABLE();}
#else
    static void initClockPortC() {}
#endif
#ifdef GPIOD
    static void initClockPortD() { __HAL_RCC_GPIOD_CLK_ENABLE();}
#else
    static void initClockPortD() {}
#endif
#ifdef GPIOE
    static void initClockPortE() { __HAL_RCC_GPIOE_CLK_ENABLE();}
#else
    static void initClockPortE() {}
#endif
#ifdef GPIOF
    static void initClockPortF() { __HAL_RCC_GPIOF_CLK_ENABLE();}
#else
    static void initClockPortF() {}
#endif
#ifdef GPIOG
    static void initClockPortG() { __HAL_RCC_GPIOG_CLK_ENABLE();}
#else
    static void initClockPortG() {}
#endif
#ifdef GPIOH
    static void initClockPortH() { __HAL_RCC_GPIOH_CLK_ENABLE();}
#else
    static void initClockPortH() {}
#endif
#ifdef GPIOI
    static void initClockPortI() { __HAL_RCC_GPIOI_CLK_ENABLE();}
#else
    static void initClockPortI() {}
#endif
#ifdef GPIOJ
    static void initClockPortJ() { __HAL_RCC_GPIOJ_CLK_ENABLE();}
#else
    static void initClockPortJ() {}
#endif
#ifdef GPIOK
    static void initClockPortK() { __HAL_RCC_GPIOK_CLK_ENABLE();}
#else
    static void initClockPortK() {}
#endif