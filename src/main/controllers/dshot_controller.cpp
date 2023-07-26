#include "dshot_controller.hpp"

#include "drivers/pal/dma.hpp"
#include "drivers/pal/timer.hpp"

#include <etl/span.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wuseless-cast"

/**
 * First just a quick implementation of the dshot protocol in order to test how it works.
 * Later refactor properly
*/

/**
 * Our board uses the following pinout: 
 *  PE9    ->  TIM1_CH1 
 *  PE11   ->  TIM1_CH2
 *  PE13   ->  TIM1_CH3
 *  PE14   ->  TIM1_CH4
*/

#define MOTOR_1_BIT 687/2
#define MOTOR_0_BIT 343/2

// Define the memory buffer size and values for duty cycle
#define BUFFER_SIZE 18
uint32_t duty_cycle_buffer[BUFFER_SIZE] = {
    MOTOR_0_BIT,
    MOTOR_0_BIT,
    MOTOR_0_BIT,
    MOTOR_0_BIT,
    MOTOR_0_BIT,
    MOTOR_0_BIT,
    MOTOR_0_BIT,
    MOTOR_0_BIT,
    MOTOR_0_BIT,
    MOTOR_0_BIT,
    MOTOR_0_BIT,
    MOTOR_0_BIT,
    MOTOR_0_BIT,
    MOTOR_0_BIT,
    MOTOR_0_BIT,
    MOTOR_0_BIT,
    0,
    0
};

dshot_controller::dshot_controller()
    : Runnable(__func__, Runnable::initThreadAttr(__func__, 4096, osPriorityNormal)),
    m_dshot(dshot::DSHOT_600)
{
}

void dshot_controller::Run()
{   
    // uint32_t counter = 0;
    while (true)
    {
        // Wait some time
        // Write to motors a value
        // if (counter > 1900) counter = 0;
        osDelay(1000);
        // counter += 100; 
        // m_dshot.write(counter);
    }
    
}

void dshot_controller::Init()
{

}


#pragma GCC diagnostic pop
