#pragma once

#include <etl/unordered_map.h>

#include "drivers/platform.hpp"
#include "drivers/pal/uart.hpp"
#include "drivers/pal/global_io.hpp"


#define UART_MAX_PINS 5
#define UARTDEV_COUNT 9

// TODO: Look for refactoring this

namespace pal {

    namespace stm32 {

        struct io_info_t {
            pal::io_id id;
            GPIO_TypeDef* port;
            uint16_t pin;
            uint8_t af;

            inline bool operator==(const io_info_t& other) const { return (id == other.id); }
            inline bool operator==(const pal::io_id& other) const { return (id == other); }   
        };

        struct uart_hardware_t {
            USART_TypeDef* reg;
        #ifdef USE_DMA
            DMA_Request_TypeDef rxDMAChannel;
            dmaResource_t *rxDMAResource;
            DMA_Request_TypeDef txDMAChannel;
            dmaResource_t *txDMAResource;
        #endif
            etl::array<io_info_t, UART_MAX_PINS> rxPins;
            etl::array<io_info_t, UART_MAX_PINS> txPins;
            uint32_t rcc;
            IRQn_Type rxIrq;
            // uint8_t txPriority;  Commented out for now
            // uint8_t rxPriority;
        };
        
    }
};  // namespace pal


