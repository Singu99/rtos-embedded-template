#pragma once

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

private:
    void init_handle();

private:
    TIM_HandleTypeDef m_handle;

};