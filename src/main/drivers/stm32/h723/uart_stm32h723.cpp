#include "drivers/platform.hpp"
#include "drivers/rcc.hpp"
#include "drivers/common/hardware.hpp"
#include "drivers/stm32/common/stm32_uart_impl.hpp"

#define USE_UART1
#define USE_UART2
#define USE_UART3
#define USE_UART4
#define USE_UART5
#define USE_UART6
#define USE_UART7
#define USE_UART8
#define USE_UART9

#ifndef UART1_TX_DMA_STREAM
#define UART1_TX_DMA_STREAM NULL
#endif
#ifndef UART1_RX_DMA_STREAM
#define UART1_RX_DMA_STREAM NULL
#endif
#ifndef UART2_TX_DMA_STREAM
#define UART2_TX_DMA_STREAM NULL
#endif
#ifndef UART2_RX_DMA_STREAM
#define UART2_RX_DMA_STREAM NULL
#endif
#ifndef UART3_TX_DMA_STREAM
#define UART3_TX_DMA_STREAM NULL
#endif
#ifndef UART3_RX_DMA_STREAM
#define UART3_RX_DMA_STREAM NULL
#endif
#ifndef UART4_TX_DMA_STREAM
#define UART4_TX_DMA_STREAM NULL
#endif
#ifndef UART4_RX_DMA_STREAM
#define UART4_RX_DMA_STREAM NULL
#endif
#ifndef UART5_TX_DMA_STREAM
#define UART5_TX_DMA_STREAM NULL
#endif
#ifndef UART5_RX_DMA_STREAM
#define UART5_RX_DMA_STREAM NULL
#endif
#ifndef UART6_TX_DMA_STREAM
#define UART6_TX_DMA_STREAM NULL
#endif
#ifndef UART6_RX_DMA_STREAM
#define UART6_RX_DMA_STREAM NULL
#endif
#ifndef UART7_TX_DMA_STREAM
#define UART7_TX_DMA_STREAM NULL
#endif
#ifndef UART7_RX_DMA_STREAM
#define UART7_RX_DMA_STREAM NULL
#endif
#ifndef UART8_TX_DMA_STREAM
#define UART8_TX_DMA_STREAM NULL
#endif
#ifndef UART8_RX_DMA_STREAM
#define UART8_RX_DMA_STREAM NULL
#endif
#ifndef UART9_TX_DMA_STREAM
#define UART9_TX_DMA_STREAM NULL
#endif
#ifndef UART9_RX_DMA_STREAM
#define UART9_RX_DMA_STREAM NULL
#endif
#ifndef UART10_TX_DMA_STREAM
#define UART10_TX_DMA_STREAM NULL
#endif
#ifndef UART10_RX_DMA_STREAM
#define UART10_RX_DMA_STREAM NULL
#endif

// #define USE_DMA  // TODO: Finish dma support

/* ************************************************************************************************************** */
/* @info Find the gpio to AF combination in the STM32H723 datasheet. Table 8. STM32H723 pin alternate functions   */
/* ************************************************************************************************************** */

/**
 * The idea is that user will define the hardware of the system with the hw_t struct. The struct will be hashable. We 
 * will identify the hardware by the key (uart_device_id). The struct will contain the hardware details of the device.
 * We will retrieve the hardware struct with template specialization.
*/

static const etl::unordered_map<pal::uart::id, pal::stm32::uart_hardware_t, UARTDEV_COUNT> uartHardware = {
#ifdef USE_UART1
    { 
        pal::uart::id::u1,
        {
            .reg = USART1,
    #ifdef USE_DMA
            .rxDMAChannel = DMA_REQUEST_USART1_RX,
            .rxDMAResource = (dmaResource_t *)UART1_RX_DMA_STREAM,
            .txDMAChannel = DMA_REQUEST_USART1_TX,
            .txDMAResource = (dmaResource_t *)UART1_TX_DMA_STREAM,
    #endif
            .rxPins = {{
                { {pal::port::A, pal::pin::_10}, GPIOA, GPIO_PIN_10, GPIO_AF7_USART1 },
                { {pal::port::B, pal::pin::_7},  GPIOB, GPIO_PIN_7,  GPIO_AF7_USART1 },
                { {pal::port::B, pal::pin::_15}, GPIOB, GPIO_PIN_15, GPIO_AF4_USART1 },
            }},
            .txPins = {{
                { {pal::port::A, pal::pin::_9},  GPIOA, GPIO_PIN_9,  GPIO_AF7_USART1 },
                { {pal::port::B, pal::pin::_6},  GPIOB, GPIO_PIN_6, GPIO_AF7_USART1 },
                { {pal::port::B, pal::pin::_14}, GPIOB, GPIO_PIN_14, GPIO_AF4_USART1 },
            }},
            .rcc = RCC_APB2(USART1),
            .rxIrq = USART1_IRQn
        }
    },
#endif

#ifdef USE_UART2
    { 
        pal::uart::id::u2,
        {
            .reg = USART2,
    #ifdef USE_DMA
            .rxDMAChannel = DMA_REQUEST_USART2_RX,
            .rxDMAResource = (dmaResource_t *)UART2_RX_DMA_STREAM,
            .txDMAChannel = DMA_REQUEST_USART2_TX,
            .txDMAResource = (dmaResource_t *)UART2_TX_DMA_STREAM,
    #endif
            .rxPins = {{
                {{pal::port::A, pal::pin::_3},  GPIOA, GPIO_PIN_3,  GPIO_AF7_USART2 },
                {{pal::port::D, pal::pin::_6},  GPIOD, GPIO_PIN_6,  GPIO_AF7_USART2 },
            }},
            .txPins = {{
                {{pal::port::A, pal::pin::_2},  GPIOA, GPIO_PIN_2,  GPIO_AF7_USART2 },
                {{pal::port::D, pal::pin::_5},  GPIOD, GPIO_PIN_5,  GPIO_AF7_USART2 },
            }},
            .rcc = RCC_APB1L(USART2),
            .rxIrq = USART2_IRQn
        }
    },
#endif

#ifdef USE_UART3
    { 
        pal::uart::id::u3,
        {
            .reg = USART3,
    #ifdef USE_DMA
            .rxDMAChannel = DMA_REQUEST_USART3_RX,
            .rxDMAResource = (dmaResource_t *)UART3_RX_DMA_STREAM,
            .txDMAChannel = DMA_REQUEST_USART3_TX,
            .txDMAResource = (dmaResource_t *)UART3_TX_DMA_STREAM,
    #endif
            .rxPins = {{
                {{pal::port::B, pal::pin::_11}, GPIOB, GPIO_PIN_11, GPIO_AF7_USART3 },
                {{pal::port::C, pal::pin::_11}, GPIOC, GPIO_PIN_11, GPIO_AF7_USART3 },
                {{pal::port::D, pal::pin::_9},  GPIOD, GPIO_PIN_9,  GPIO_AF7_USART3 }
            }},
            .txPins = {{
                {{pal::port::B, pal::pin::_10}, GPIOB, GPIO_PIN_10, GPIO_AF7_USART3 },
                {{pal::port::C, pal::pin::_10}, GPIOC, GPIO_PIN_10, GPIO_AF7_USART3 },
                {{pal::port::D, pal::pin::_8},  GPIOD, GPIO_PIN_8,  GPIO_AF7_USART3 },
            }},
            .rcc = RCC_APB1L(USART3),
            .rxIrq = USART3_IRQn
        }
    },
#endif

#ifdef USE_UART4
    { 
        pal::uart::id::u4,
        {
            .reg = UART4,
    #ifdef USE_DMA
            .rxDMAChannel = DMA_REQUEST_UART4_RX,
            .rxDMAResource = (dmaResource_t *)UART4_RX_DMA_STREAM,
            .txDMAChannel = DMA_REQUEST_UART4_TX,
            .txDMAResource = (dmaResource_t *)UART4_TX_DMA_STREAM,
    #endif
            .rxPins = {{
                {{pal::port::A, pal::pin::_1},  GPIOA, GPIO_PIN_1,  GPIO_AF8_UART4 },
                {{pal::port::A, pal::pin::_10}, GPIOA, GPIO_PIN_10, GPIO_AF6_UART4 },
                {{pal::port::B, pal::pin::_8},  GPIOB, GPIO_PIN_8, GPIO_AF8_UART4 },
                {{pal::port::C, pal::pin::_11}, GPIOC, GPIO_PIN_11, GPIO_AF8_UART4 },
                {{pal::port::D, pal::pin::_0},  GPIOD, GPIO_PIN_0,  GPIO_AF8_UART4 }
            }},
            .txPins = {{
                {{pal::port::A, pal::pin::_0},  GPIOA, GPIO_PIN_0,  GPIO_AF8_UART4 },
                {{pal::port::A, pal::pin::_12}, GPIOA, GPIO_PIN_12, GPIO_AF6_UART4 },
                {{pal::port::B, pal::pin::_9}, GPIOB, GPIO_PIN_9, GPIO_AF8_UART4 },
                {{pal::port::C, pal::pin::_10}, GPIOC, GPIO_PIN_10, GPIO_AF8_UART4 },
                {{pal::port::D, pal::pin::_1},  GPIOD, GPIO_PIN_1,  GPIO_AF8_UART4 }
            }},
            .rcc = RCC_APB1L(UART4),
            .rxIrq = UART4_IRQn
        },
    },
#endif

#ifdef USE_UART5
    { 
        pal::uart::id::u4,
        {
            .reg = UART5,
    #ifdef USE_DMA
            .rxDMAChannel = DMA_REQUEST_UART5_RX,
            .rxDMAResource = (dmaResource_t *)UART5_RX_DMA_STREAM,
            .txDMAChannel = DMA_REQUEST_UART5_TX,
            .txDMAResource = (dmaResource_t *)UART5_TX_DMA_STREAM,
    #endif
            .rxPins = {{
                {{pal::port::B, pal::pin::_6}, GPIOB, GPIO_PIN_6,  GPIO_AF14_UART5 },
                {{pal::port::B, pal::pin::_13}, GPIOB, GPIO_PIN_13, GPIO_AF14_UART5 },
                {{pal::port::C, pal::pin::_12}, GPIOC, GPIO_PIN_12, GPIO_AF8_UART5 },
            }},
            .txPins = {{
                {{pal::port::B, pal::pin::_5},  GPIOB, GPIO_PIN_5,  GPIO_AF14_UART5 },
                {{pal::port::B, pal::pin::_12}, GPIOB, GPIO_PIN_12, GPIO_AF14_UART5 },
                {{pal::port::C, pal::pin::_11}, GPIOC, GPIO_PIN_11, GPIO_AF8_UART5 },
            }},
            .rcc = RCC_APB1L(UART5),
            .rxIrq = UART5_IRQn
        }
    },
#endif

#ifdef USE_UART6
    { 
        pal::uart::id::u6,
        {
            .reg = USART6,
    #ifdef USE_DMA
            .rxDMAChannel = DMA_REQUEST_USART6_RX,
            .rxDMAResource = (dmaResource_t *)UART6_RX_DMA_STREAM,
            .txDMAChannel = DMA_REQUEST_USART6_TX,
            .txDMAResource = (dmaResource_t *)UART6_TX_DMA_STREAM,
    #endif
            .rxPins = {{
                { {pal::port::C, pal::pin::_7}, GPIOC, GPIO_PIN_7, GPIO_AF7_USART6 },
                { {pal::port::G, pal::pin::_9}, GPIOG, GPIO_PIN_9, GPIO_AF7_USART6 },
            }},
            .txPins = {{
                {{pal::port::C, pal::pin::_6}, GPIOC, GPIO_PIN_6, GPIO_AF7_USART6 },
                {{pal::port::G, pal::pin::_14}, GPIOG, GPIO_PIN_14, GPIO_AF7_USART6 },
            }},
            .rcc = RCC_APB2(USART6),
            .rxIrq = USART6_IRQn
        }
    },
#endif

#ifdef USE_UART7
    { 
        pal::uart::id::u7,
        {
            .reg = UART7,
    #ifdef USE_DMA
            .rxDMAChannel = DMA_REQUEST_UART7_RX,
            .rxDMAResource = (dmaResource_t *)UART7_RX_DMA_STREAM,
            .txDMAChannel = DMA_REQUEST_UART7_TX,
            .txDMAResource = (dmaResource_t *)UART7_TX_DMA_STREAM,
    #endif
            .rxPins = {{
                {{pal::port::A, pal::pin::_8}, GPIOA, GPIO_PIN_8, GPIO_AF11_UART7 },
                {{pal::port::B, pal::pin::_3}, GPIOB, GPIO_PIN_3, GPIO_AF11_UART7 },
                {{pal::port::E, pal::pin::_7}, GPIOE, GPIO_PIN_7, GPIO_AF7_UART7 },
                {{pal::port::F, pal::pin::_6}, GPIOF, GPIO_PIN_6, GPIO_AF7_UART7},
            }},
            .txPins = {{
                {{pal::port::A, pal::pin::_15}, GPIOA, GPIO_PIN_15, GPIO_AF11_UART7 },
                {{pal::port::B, pal::pin::_4},  GPIOB, GPIO_PIN_4,  GPIO_AF11_UART7 },
                {{pal::port::E, pal::pin::_8},  GPIOE, GPIO_PIN_8,  GPIO_AF7_UART7 },
                {{pal::port::F, pal::pin::_7},  GPIOF, GPIO_PIN_7,  GPIO_AF7_UART7 },
            }},
            .rcc = RCC_APB1L(UART7),
            .rxIrq = UART7_IRQn
        }
    },
#endif

#ifdef USE_UART8
    { 
        pal::uart::id::u8,
        {
            .reg = UART8,
    #ifdef USE_DMA
            .rxDMAChannel = DMA_REQUEST_UART8_RX,
            .rxDMAResource = (dmaResource_t *)UART8_RX_DMA_STREAM,
            .txDMAChannel = DMA_REQUEST_UART8_TX,
            .txDMAResource = (dmaResource_t *)UART8_TX_DMA_STREAM,
    #endif
            .rxPins = {{
                {{pal::port::E, pal::pin::_0}, GPIOE, GPIO_PIN_0, GPIO_AF8_UART8 },
            }},
            .txPins = {{
                {{pal::port::E, pal::pin::_1}, GPIOE, GPIO_PIN_1, GPIO_AF8_UART8 },
            }},
            .rcc = RCC_APB1L(UART8),
            .rxIrq = UART8_IRQn
        }
    },
#endif

#ifdef USE_UART9
    { 
        pal::uart::id::u9,
        {
            .reg = UART9,
    #ifdef USE_DMA
            .rxDMAChannel = DMA_REQUEST_UART9_RX,
            .rxDMAResource = (dmaResource_t *)UART9_RX_DMA_STREAM,
            .txDMAChannel = DMA_REQUEST_UART9_TX,
            .txDMAResource = (dmaResource_t *)UART9_TX_DMA_STREAM,
    #endif
            .rxPins = {{
                {{pal::port::D, pal::pin::_14}, GPIOD, GPIO_PIN_14, GPIO_AF11_UART9 },
            }},
            .txPins = {{
                {{pal::port::D, pal::pin::_15}, GPIOD, GPIO_PIN_15, GPIO_AF11_UART9 },
            }},
            .rcc = RCC_APB2(UART9),
            .rxIrq = UART9_IRQn
        }
    }
#endif

#ifdef USE_UART10
    {
        .device = UARTDEV_10,
        .reg = USART10,
#ifdef USE_DMA
        .rxDMAChannel = DMA_REQUEST_USART10_RX,
        .rxDMAResource = (dmaResource_t *)UART10_RX_DMA_STREAM,
        .txDMAChannel = DMA_REQUEST_USART10_TX,
        .txDMAResource = (dmaResource_t *)UART10_TX_DMA_STREAM,
#endif
        .rxPins = {
            { DEFIO_TAG_E(PE2), GPIO_AF11_USART10 }
        },
        .txPins = {
            { DEFIO_TAG_E(PE3), GPIO_AF11_USART10 }
        },
        .rcc = RCC_APB2(USART10),
        .rxIrq = USART10_IRQn,
        .txPriority = NVIC_PRIO_SERIALUART10_TXDMA,
        .rxPriority = NVIC_PRIO_SERIALUART10,
        .txBuffer = uart10TxBuffer,
        .rxBuffer = uart10RxBuffer,
        .txBufferSize = sizeof(uart10TxBuffer),
        .rxBufferSize = sizeof(uart10RxBuffer),
    },
#endif

#ifdef USE_LPUART1
    {
        .device = LPUARTDEV_1,
        .reg = LPUART1,
#ifdef USE_DMA
        .rxDMAChannel = BDMA_REQUEST_LPUART1_RX,
        .rxDMAResource = (dmaResource_t *)NULL, // No DMA support yet (Need BDMA support)
        .txDMAChannel = BDMA_REQUEST_LPUART1_TX,
        .txDMAResource = (dmaResource_t *)NULL, // No DMA support yet (Need BDMA support)
#endif
        .rxPins = {
            { DEFIO_TAG_E(PA10), GPIO_AF3_LPUART },
            { DEFIO_TAG_E(PB7),  GPIO_AF8_LPUART }
        },
        .txPins = {
            { DEFIO_TAG_E(PA9),  GPIO_AF3_LPUART },
            { DEFIO_TAG_E(PB6),  GPIO_AF8_LPUART }
        },
        .rcc = RCC_APB4(LPUART1),
        .rxIrq = LPUART1_IRQn,
        .txPriority = NVIC_PRIO_SERIALLPUART1_TXDMA, // Not used until DMA is supported
        .rxPriority = NVIC_PRIO_SERIALLPUART1,       // Not used until DMA is supported
        .txBuffer = lpuart1TxBuffer,
        .rxBuffer = lpuart1RxBuffer,
        .txBufferSize = sizeof(lpuart1TxBuffer),
        .rxBufferSize = sizeof(lpuart1RxBuffer),
    },
#endif
};

// Hardware template specialization for retrieving stm32h723 uart hardware details
template <>
template <>
const pal::stm32::uart_hardware_t* hardware<pal::stm32::uart_hardware_t>::get(pal::uart::id id) {
    // return &uartHardware.at(id);
    // Bug. Why calling the operator equal is causing hard fault? Fix:  
    return &uartHardware.at(id);
}

