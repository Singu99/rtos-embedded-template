#include <array>

#include "drivers/stm32/common/stm32_gpio.hpp"
#include "stm32_gpio.hpp"

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
static const std::array<void(*)(), 11> initClockPort = {{
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
}};

/**
 * @brief: Configure GPIO pin for UART
 */
stm32_gpio::stm32_gpio(pal::port port, pal::pin pin)
    : pal::gpio(port, pin)
{
    // initClockPort(port);
    // initPin(port, pin);
}

void stm32_gpio::set()
{

}

void stm32_gpio::reset()
{
}

void stm32_gpio::toggle()
{
}

bool stm32_gpio::read()
{
    return false;
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





