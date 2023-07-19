#include "stm32_timer.hpp"
#include "stm32_timer_impl.hpp"
#include "drivers/common/hardware.hpp"


timer_device_stm32::timer_device_stm32(pal::timer::id dev_id)
    : timer_device(dev_id)
{
    init_handle();
}

void timer_device_stm32::configure_timebase(uint32_t period, uint32_t prescaler)
{
    m_handle.Init.Period = period;
    m_handle.Init.Prescaler = prescaler;
    m_handle.Init.ClockDivision = 0;
    m_handle.Init.CounterMode = TIM_COUNTERMODE_UP;
    m_handle.Init.RepetitionCounter = 0;
    m_handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    HAL_TIM_Base_Init(&m_handle);
}

void timer_device_stm32::start()
{
    HAL_TIM_Base_Start(&m_handle);
}

void timer_device_stm32::stop()
{
    HAL_TIM_Base_Stop(&m_handle);
}

/**
 * @brief Reset the internal counter of the timer
*/
void timer_device_stm32::reset()
{
    __HAL_TIM_SET_COUNTER(&m_handle, 0);
}

uint32_t timer_device_stm32::get_counter()
{
    return __HAL_TIM_GET_COUNTER(&m_handle);
}

void timer_device_stm32::init_handle()
{
    const auto* tim_hw = hardware<pal::stm32::timer_hardware_t>::get(m_dev_id);
    m_handle.Instance = tim_hw->reg;
}