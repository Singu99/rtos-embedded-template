#pragma once

#include "drivers/platform.hpp"
#include "drivers/pal/uart.hpp"

#define UART_MAX_PINS 5
#define UARTDEV_COUNT 10

namespace pal {

    namespace stm32 {

        struct gpio_t {
            GPIO_TypeDef* port;
            uint16_t pin;
            uint8_t af;
        };

        namespace uart {

            struct hw_t {
                pal::uart::id device;
                USART_TypeDef* reg;
            #ifdef USE_DMA
                DMA_Request_TypeDef rxDMAChannel;
                dmaResource_t *rxDMAResource;
                DMA_Request_TypeDef txDMAChannel;
                dmaResource_t *txDMAResource;
            #endif
                gpio_t rxPins[UART_MAX_PINS];
                gpio_t txPins[UART_MAX_PINS];
                uint32_t rcc;
                IRQn_Type rxIrq;
                // uint8_t txPriority;  Commented out for now
                // uint8_t rxPriority;
            };
        }
    }
};  // namespace pal


