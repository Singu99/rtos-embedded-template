#include <etl/array.h>

#include "drivers/pal/global_io.hpp"

#include "drivers/stm32/common/stm32_uart_impl.hpp"

#include "drivers/common/hardware.hpp"



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

/**
 * @brief: gpio clock table
 */
static const etl::unordered_map<pal::port, void(*)(), static_cast<size_t>(pal::port::COUNT)> initClockPort = {
    { pal::port::A, initClockPortA},
    { pal::port::B, initClockPortB},
    { pal::port::C, initClockPortC},
    { pal::port::D, initClockPortD},
    { pal::port::E, initClockPortE},
    { pal::port::F, initClockPortF},
    { pal::port::G, initClockPortG},
    { pal::port::H, initClockPortH},
    { pal::port::I, initClockPortI},
    { pal::port::J, initClockPortJ},
    { pal::port::K, initClockPortK}
};



void pal::global_io::configure_pin(pal::uart::id uart_id, io_id io)
{
    const auto uartHardware = hardware<pal::stm32::uart_hardware_t>::get(uart_id);

    // Enable clock for port
    initClockPort.at(io.port_id)();

    // Get hardware specific pin and port
    auto rx_it = etl::find(uartHardware->rxPins.begin(), uartHardware->rxPins.end(), io);

    GPIO_InitTypeDef GPIO_InitStruct = {};
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    if (rx_it != uartHardware->rxPins.end()) {
        // Configure the rx pin
        GPIO_InitStruct.Pin = rx_it->pin;
        GPIO_InitStruct.Alternate = rx_it->af;
        HAL_GPIO_Init(rx_it->port, &GPIO_InitStruct);
        return;
    }

    auto tx_it = etl::find(uartHardware->txPins.begin(), uartHardware->txPins.end(), io);
    if (tx_it != uartHardware->txPins.end()) {
        // Configure the tx pin
        GPIO_InitStruct.Pin = tx_it->pin;
        GPIO_InitStruct.Alternate = tx_it->af;
        HAL_GPIO_Init(tx_it->port, &GPIO_InitStruct);
        return;
    }
    // TODO: Return error state
}

void pal::global_io::configure_pin(pal::timer::id timer_id, io_id io)
{
    
}


/* gpio clock inits */
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





