#pragma once

#include "drivers/platform.hpp"
#include "drivers/pal/uart.hpp"
#include "drivers/pal/gpio.hpp"

#define UART_MAX_PINS 5
#define UARTDEV_COUNT 9

namespace pal {

    namespace stm32 {

        struct gpio_stm32 {
            gpio_stm32() = default;
            gpio_stm32(pal::gpio gpio, GPIO_TypeDef* port, uint16_t pin, uint8_t af) 
                : gpio(gpio), port(port), pin(pin), af(af) {}

            pal::gpio gpio;   
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
                gpio_stm32 rxPins[UART_MAX_PINS];
                gpio_stm32 txPins[UART_MAX_PINS];
                uint32_t rcc;
                IRQn_Type rxIrq;
                // uint8_t txPriority;  Commented out for now
                // uint8_t rxPriority;
            };
        }
    }
};  // namespace pal


