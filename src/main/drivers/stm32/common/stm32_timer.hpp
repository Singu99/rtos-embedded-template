#pragma once

#include <etl/span.h>

#include "drivers/platform.hpp"
#include "drivers/pal/timer.hpp"

#include <cstdint>

class timer_device_stm32 : public pal::timer_device {
public:
    timer_device_stm32(pal::timer::id dev_id);
    ~timer_device_stm32() = default;

    virtual void configure_timebase(uint32_t period, uint32_t prescaler) override;
    virtual void start() override;
    virtual void stop() override;
    virtual void reset() override;
    virtual uint32_t get_counter() override;

    virtual void configure_pwm(uint32_t prescaler, uint32_t period, pal::timer::channel channel) override;
    virtual void stop_pwm(pal::timer::channel channel) override;

    virtual void pause_pwm() override;
    virtual void resume_pwm() override;

    inline TIM_HandleTypeDef* get_handle() { return &m_handle; }

protected:
    virtual void start_pwm(pal::timer::channel channel, uint32_t* buffer, uint32_t lenght) override;

private:
    void init_handle();

private:
    TIM_HandleTypeDef m_handle;

};