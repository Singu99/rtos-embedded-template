#include <etl/array.h>
#include <etl/map.h>

#include "drivers/pal/global_io.hpp"

#include "drivers/stm32/common/stm32_uart_impl.hpp"
#include "drivers/stm32/common/stm32_timer_impl.hpp"

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
static const etl::map<pal::port, void(*)(), static_cast<size_t>(pal::port::COUNT)> initClockPort = {
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

static const etl::map<pal::port, GPIO_TypeDef*, static_cast<size_t>(pal::port::COUNT)> portToGpio = {
    { pal::port::A, GPIOA},
    { pal::port::B, GPIOB},
    { pal::port::C, GPIOC},
    { pal::port::D, GPIOD},
    { pal::port::E, GPIOE},
    { pal::port::F, GPIOF},
    { pal::port::G, GPIOG},
    { pal::port::H, GPIOH},
    #ifdef GPIOI
    { pal::port::I, GPIOI},
    #endif
    { pal::port::J, GPIOJ},
    { pal::port::K, GPIOK}
};

static const etl::map<pal::pin, uint32_t, static_cast<size_t>(pal::pin::COUNT)> pinToGpioPin = {
    { pal::pin::_0, GPIO_PIN_0},
    { pal::pin::_1, GPIO_PIN_1},
    { pal::pin::_2, GPIO_PIN_2},
    { pal::pin::_3, GPIO_PIN_3},
    { pal::pin::_4, GPIO_PIN_4},
    { pal::pin::_5, GPIO_PIN_5},
    { pal::pin::_6, GPIO_PIN_6},
    { pal::pin::_7, GPIO_PIN_7},
    { pal::pin::_8, GPIO_PIN_8},
    { pal::pin::_9, GPIO_PIN_9},
    { pal::pin::_10, GPIO_PIN_10},
    { pal::pin::_11, GPIO_PIN_11},
    { pal::pin::_12, GPIO_PIN_12},
    { pal::pin::_13, GPIO_PIN_13},
    { pal::pin::_14, GPIO_PIN_14},
    { pal::pin::_15, GPIO_PIN_15}
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

// Refactor this
void pal::global_io::configure_pin(pal::timer::id timer_id, pal::timer::channel channel, io_id io)
{
    const auto timerHardware = hardware<pal::stm32::timer_hardware_t>::get(timer_id);

    // Enable clock for port
    initClockPort.at(io.port_id)();

    GPIO_InitTypeDef GPIO_InitStruct = {};
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Pin = pinToGpioPin.at(io.pin_id);
    GPIO_InitStruct.Alternate = timerHardware->channels[static_cast<uint32_t>(channel)].af;
    HAL_GPIO_Init(portToGpio.at(io.port_id), &GPIO_InitStruct);
}


//****************
// Module mappings
//****************


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





