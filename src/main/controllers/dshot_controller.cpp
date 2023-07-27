#include "dshot_controller.hpp"

#include "drivers/pal/dma.hpp"
#include "drivers/pal/timer.hpp"

#include "mcu.hpp"

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
#define MOTOR_0_BIT 308/2


dshot_controller::dshot_controller()
    : Runnable(__func__, Runnable::initThreadAttr(__func__, 4096, osPriorityNormal)),
    m_dshot(dshot::DSHOT_600)
{



}


void dshot_controller::Run()
{   


    while (true)
    {
        osDelay(1);            // simulating a 0.1 KHz update rate

        if (mcu::rx->getChannel(0) > 1300)
        {
            // Scaling from 1300 - 2000 to 48 - 648
            uint32_t value = ((mcu::rx->getChannel(0) - 1300) * 600 / 700 ) + 48;
            m_dshot.write(value);
        }
        else{
            m_dshot.write(0);   // Disarmed command
        }
    }    
}

void dshot_controller::Init()
{

}


#pragma GCC diagnostic pop
