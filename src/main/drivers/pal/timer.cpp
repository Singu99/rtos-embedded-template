#include <etl/array.h>

#include "timer.hpp"

#include "target/target.h"

#include "isr.hpp"

/* **** Architectures Start **** */
#ifdef STM32
// Forward declaration of hardware specific class
#include "drivers/stm32/common/stm32_timer.hpp"
#define timer_device_hw timer_device_stm32
#elif ESP32
#include "drivers/esp32/common/uart_esp32.hpp"
#else
#error "No architecture defined"
#endif
/* **** Architectures End **** */

namespace pal {

    static constexpr size_t timer_count = static_cast<size_t>(pal::timer::id::COUNT);
    static const etl::array<isr::vector_id, timer_count> vector_ids = {
        isr::vector_id::TIM1_IRQ_HANDLER,
        isr::vector_id::TIM2_IRQ_HANDLER,
        isr::vector_id::TIM3_IRQ_HANDLER,
        isr::vector_id::TIM4_IRQ_HANDLER,
        isr::vector_id::TIM5_IRQ_HANDLER,
        isr::vector_id::TIM6_IRQ_HANDLER,
        isr::vector_id::TIM7_IRQ_HANDLER,
        isr::vector_id::TIM8_IRQ_HANDLER,
        isr::vector_id::TIM12_IRQ_HANDLER,
        isr::vector_id::TIM13_IRQ_HANDLER,
        isr::vector_id::TIM14_IRQ_HANDLER,
        isr::vector_id::TIM15_IRQ_HANDLER,
        isr::vector_id::TIM16_IRQ_HANDLER,
        isr::vector_id::TIM17_IRQ_HANDLER
    };


    pal::timer_device::timer_device(timer::id dev_id)
        : device(), m_dev_id(dev_id)
    {
    }

    /* TODO: ISR Stuff */

}


// ***********************************************************************************
// Template speciallization for getting devices specific instances. Used by device.hpp
// ***********************************************************************************
template<>
pal::timer_device* device::get<pal::timer_device>(pal::timer::id dev_id)
{
    static constexpr size_t timer_count = static_cast<size_t>(pal::timer::id::COUNT);
    static etl::array<timer_device_hw, timer_count> timer_devices = {{
        { timer_device_hw(pal::timer::id::t1)},
        { timer_device_hw(pal::timer::id::t2)},
        { timer_device_hw(pal::timer::id::t3)},
        { timer_device_hw(pal::timer::id::t4)},
        { timer_device_hw(pal::timer::id::t5)},
        { timer_device_hw(pal::timer::id::t6)},
        { timer_device_hw(pal::timer::id::t7)},
        { timer_device_hw(pal::timer::id::t8)},
        { timer_device_hw(pal::timer::id::t9)},
        { timer_device_hw(pal::timer::id::t12)},
        { timer_device_hw(pal::timer::id::t13)},
        { timer_device_hw(pal::timer::id::t14)},
        { timer_device_hw(pal::timer::id::t15)},
        { timer_device_hw(pal::timer::id::t16)},
        { timer_device_hw(pal::timer::id::t17)}
    }};

    return &timer_devices[static_cast<uint32_t>(dev_id)];
}
