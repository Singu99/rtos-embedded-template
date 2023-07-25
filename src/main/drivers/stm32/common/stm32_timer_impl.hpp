#pragma once

#include <etl/unordered_map.h>

#include "drivers/platform.hpp"
#include "drivers/pal/timer.hpp"
#include "drivers/pal/global_io.hpp"

#define UART_MAX_PINS 5
#define UARTDEV_COUNT 9

// TODO: Look for refactoring this

namespace pal {

    namespace stm32 {

        struct timer_channel_hw_t
        {
            uint32_t af;
            uint32_t dma_req;
        };

        struct timer_hardware_t {
            TIM_TypeDef* reg;
            uint32_t rcc;
            IRQn_Type isr;
            timer_channel_hw_t channels[4];
        };
        
    }
};  // namespace pal
