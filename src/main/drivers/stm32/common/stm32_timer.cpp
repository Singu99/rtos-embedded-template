#include "stm32_timer.hpp"
#include "stm32_timer_impl.hpp"
#include "drivers/common/hardware.hpp"
#include "drivers/rcc.hpp"

static constexpr uint32_t CHANNEL_COUNT = static_cast<size_t>(pal::timer::channel::COUNT);
static constexpr inline etl::array<uint32_t, CHANNEL_COUNT> get_channel_map()
{
    etl::array<uint32_t, CHANNEL_COUNT> channel_map = {TIM_CHANNEL_1, TIM_CHANNEL_2, TIM_CHANNEL_3, TIM_CHANNEL_4 };
    return channel_map;
}


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
    uint32_t counter = __HAL_TIM_GET_COUNTER(&m_handle);
    return counter;
}

void timer_device_stm32::configure_pwm(uint32_t prescaler, uint32_t period, pal::timer::channel channel)
{
    // Configure gpio
    // global_io::configure_pin(m_dev_id, config::get_timer_channel_io_id(m_dev_id, channel));

    // Configure timer handle
    m_handle.Init.Prescaler = prescaler;
    m_handle.Init.Period = period;
    m_handle.Init.ClockDivision = 0;
    m_handle.Init.CounterMode = TIM_COUNTERMODE_UP;
    m_handle.Init.RepetitionCounter = 0;
    m_handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    HAL_TIM_PWM_Init(&m_handle);

    TIM_OC_InitTypeDef sConfigOC;
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

    // Configure PWM channel
    const auto channel_map = get_channel_map();
    HAL_TIM_PWM_ConfigChannel(&m_handle, &sConfigOC, channel_map[static_cast<size_t>(channel)]);

}

void timer_device_stm32::start_pwm(pal::timer::channel channel, uint32_t* buffer, uint32_t lenght)
{
    const auto channel_map = get_channel_map();
    HAL_TIM_PWM_Start_DMA(&m_handle, channel_map[static_cast<size_t>(channel)], buffer, lenght);
}

void timer_device_stm32::stop_pwm(pal::timer::channel channel)
{
    const auto channel_map = get_channel_map();
    HAL_TIM_PWM_Stop_DMA(&m_handle, channel_map[static_cast<size_t>(channel)]);
}

void timer_device_stm32::init_handle()
{
    const auto* tim_hw = hardware<pal::stm32::timer_hardware_t>::get(m_dev_id);
    m_handle.Instance = tim_hw->reg;

    // Init timer clock
    RCC_ClockCmd(tim_hw->rcc, ENABLE);
}