#include "core_controller.hpp"
#include <etl/delegate.h>
#include "mcu.hpp"
#include "main.h"


// Initializes GPIOD PIN 2
static void LED_GPIO_Init()
{
    // GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_SET);

    /*Configure GPIO pin : PD2 */
    GPIO_InitTypeDef GPIO_InitStruct = {};
    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
    GPIO_InitStruct.Pin = GPIO_PIN_3;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
    GPIO_InitStruct.Pin = GPIO_PIN_4;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}


core_controller::core_controller()
    : Runnable(__func__, Runnable::initThreadAttr(__func__, 4096, osPriorityNormal)), m_uart(nullptr) // TODO: Provide empty devices for erros on claim
{
    LED_GPIO_Init();
}

// Running thread will execute this function
void core_controller::Run()
{
    // Init GPIOD PIN 2 using HAL library
    pal::timer_device* timer = device::claim_device<pal::timer_device>(pal::timer::id::t5, io::resource_id::FILE_STREAM);
    timer->configure_timebase(0xFFFFFFFF, 1000);
    timer->start();
    // Toggle the leds every 1 second
    while (true)
    {
        while(timer->get_counter() < 100000);
        timer->reset();
        if (mcu::rx->getChannel(0) < 1300)
        {
            HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_4);
            HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_SET);
        }
        else if (mcu::rx->getChannel(0) > 1700)
        {
            HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_2);
            HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_SET);
        }
        else {
            HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_3);
            HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_SET);
        }        
    }
    
}

void core_controller::Init()
{   


}

void core_controller::interrupt_handler(size_t id)
{



}
