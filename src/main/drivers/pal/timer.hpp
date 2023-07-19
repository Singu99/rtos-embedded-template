#pragma once

#include "drivers/common/device.hpp"


namespace pal {

    namespace timer {
        enum class id {t1, t2, t3, t4, t5, t6, t7, t8, t9, t12, t13, t14, t15, t16, t17, COUNT};

    }


    class timer_device : public device {
    public:
        // TODO: rsi...
        virtual void configure_timebase(uint32_t period, uint32_t prescaler) = 0;
        virtual void start() = 0;
        virtual void stop() = 0;
        virtual void reset() = 0;
        virtual uint32_t get_counter() = 0;

        timer_device(timer::id dev_id);
        ~timer_device() = default;
    protected:
        timer::id m_dev_id;

    };





}


