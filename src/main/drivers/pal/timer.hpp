#pragma once

#include "drivers/common/device.hpp"

#include <etl/span.h>

namespace pal {

    namespace timer {
        enum class id {t1, t2, t3, t4, t5, t6, t7, t8, t9, t12, t13, t14, t15, t16, t17, COUNT};
        enum class channel {ch1, ch2, ch3, ch4, COUNT};
    }


    class timer_device : public device {
    public:
        // TODO: rsi...
        virtual void configure_timebase(uint32_t period, uint32_t prescaler) = 0;
        virtual void start() = 0;
        virtual void stop() = 0;
        virtual void reset() = 0;
        virtual uint32_t get_counter() = 0;

        virtual void configure_pwm(uint32_t prescaler, uint32_t period, timer::channel channel) = 0;

        template<typename T>
        void start_pwm(pal::timer::channel channel, etl::span<T> buffer) { start_pwm(channel, static_cast<uint32_t*>(buffer.data()), buffer.size());}

        virtual void stop_pwm(pal::timer::channel channel) = 0;

        timer::id get_id() const { return m_dev_id; }

        timer_device(timer::id dev_id);
        ~timer_device() = default;

    protected:
        virtual void start_pwm(timer::channel channel, uint32_t* buffer, uint32_t lenght) = 0;

    protected:
        timer::id m_dev_id;

    };





}


