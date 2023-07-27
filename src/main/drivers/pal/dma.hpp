#pragma once

#include <cstdint>

#include <etl/delegate_service.h>

#include "drivers/common/device.hpp"
#include "drivers/pal/timer.hpp"

namespace pal {

    namespace dma {
        enum id : uint32_t {
            _1, _2, _3, _4, _5, _6, _7,
            _8, _9, _10, _11, _12, _13, 
            _14, _15, _16, COUNT
        };
    }


    class dma_device : public device {
    public:

    public: 
        dma_device();
        ~dma_device();

        virtual void configure_dma(pal::timer_device* timer, uint32_t tim_channel) = 0;

        void enable_irq(etl::delegate<void(size_t)> callback);

        void deinit();

    protected: 
        virtual void enable_irq_impl() = 0;

    protected:
        dma::id m_dma_id;
        bool active;
    };

}