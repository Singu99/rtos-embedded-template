#include <array>

#include "drivers/platform.hpp"
#include "drivers/rcc.h"
#include "drivers/common/hardware.hpp"
#include "drivers/stm32/common/stm32_uart_impl.hpp"
#include "drivers/pal/gpio.hpp"

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

static const std::array<pal::stm32::uart::hw_t, UARTDEV_COUNT> uartHardware = {{
#ifdef USE_UART1
    {
        .device = pal::uart::id::u1,
        .reg = USART1,
#ifdef USE_DMA
        .rxDMAChannel = DMA_REQUEST_USART1_RX,
        .rxDMAResource = (dmaResource_t *)UART1_RX_DMA_STREAM,
        .txDMAChannel = DMA_REQUEST_USART1_TX,
        .txDMAResource = (dmaResource_t *)UART1_TX_DMA_STREAM,
#endif
        .rxPins = {
            { {pal::port::a, pal::pin::p10}, GPIOA, GPIO_PIN_10, GPIO_AF7_USART1 },
            { {pal::port::b, pal::pin::p7},  GPIOB, GPIO_PIN_7,  GPIO_AF7_USART1 },
            { {pal::port::b, pal::pin::p15}, GPIOB, GPIO_PIN_15, GPIO_AF4_USART1 },
        },
        .txPins = {
            { {pal::port::a, pal::pin::p9},  GPIOA, GPIO_PIN_9,  GPIO_AF7_USART1 },
            { {pal::port::b, pal::pin::p6},  GPIOB, GPIO_PIN_6, GPIO_AF7_USART1 },
            { {pal::port::b, pal::pin::p14}, GPIOB, GPIO_PIN_14, GPIO_AF4_USART1 },
        },
        .rcc = RCC_APB2(USART1),
        .rxIrq = USART1_IRQn
    },
#endif

#ifdef USE_UART2
    {
        .device = pal::uart::id::u2,
        .reg = USART2,
#ifdef USE_DMA
        .rxDMAChannel = DMA_REQUEST_USART2_RX,
        .rxDMAResource = (dmaResource_t *)UART2_RX_DMA_STREAM,
        .txDMAChannel = DMA_REQUEST_USART2_TX,
        .txDMAResource = (dmaResource_t *)UART2_TX_DMA_STREAM,
#endif
        .rxPins = {
            {{pal::port::a, pal::pin::p3},  GPIOA, GPIO_PIN_3,  GPIO_AF7_USART2 },
            {{pal::port::d, pal::pin::p6},  GPIOD, GPIO_PIN_6,  GPIO_AF7_USART2 }
        },
        .txPins = {
            {{pal::port::a, pal::pin::p2},  GPIOA, GPIO_PIN_2,  GPIO_AF7_USART2 },
            {{pal::port::d, pal::pin::p5},  GPIOD, GPIO_PIN_5,  GPIO_AF7_USART2 },
        },
        .rcc = RCC_APB1L(USART2),
        .rxIrq = USART2_IRQn
    },
#endif

#ifdef USE_UART3
    {
        .device = pal::uart::id::u3,
        .reg = USART3,
#ifdef USE_DMA
        .rxDMAChannel = DMA_REQUEST_USART3_RX,
        .rxDMAResource = (dmaResource_t *)UART3_RX_DMA_STREAM,
        .txDMAChannel = DMA_REQUEST_USART3_TX,
        .txDMAResource = (dmaResource_t *)UART3_TX_DMA_STREAM,
#endif
        .rxPins = {
            {{pal::port::b, pal::pin::p11}, GPIOB, GPIO_PIN_11, GPIO_AF7_USART3 },
            {{pal::port::c, pal::pin::p11}, GPIOC, GPIO_PIN_11, GPIO_AF7_USART3 },
            {{pal::port::d, pal::pin::p9},  GPIOD, GPIO_PIN_9,  GPIO_AF7_USART3 }
        },
        .txPins = {
            {{pal::port::b, pal::pin::p10}, GPIOB, GPIO_PIN_10, GPIO_AF7_USART3 },
            {{pal::port::c, pal::pin::p10}, GPIOC, GPIO_PIN_10, GPIO_AF7_USART3 },
            {{pal::port::d, pal::pin::p8},  GPIOD, GPIO_PIN_8,  GPIO_AF7_USART3 }
        },
        .rcc = RCC_APB1L(USART3),
        .rxIrq = USART3_IRQn
    },
#endif

#ifdef USE_UART4
    {
        .device = pal::uart::id::u4,
        .reg = UART4,
#ifdef USE_DMA
        .rxDMAChannel = DMA_REQUEST_UART4_RX,
        .rxDMAResource = (dmaResource_t *)UART4_RX_DMA_STREAM,
        .txDMAChannel = DMA_REQUEST_UART4_TX,
        .txDMAResource = (dmaResource_t *)UART4_TX_DMA_STREAM,
#endif
        .rxPins = {
            {{pal::port::a, pal::pin::p1},  GPIOA, GPIO_PIN_1,  GPIO_AF8_UART4 },
            {{pal::port::a, pal::pin::p10}, GPIOA, GPIO_PIN_10, GPIO_AF6_UART4 },
            {{pal::port::b, pal::pin::p8},  GPIOB, GPIO_PIN_8, GPIO_AF8_UART4 },
            {{pal::port::c, pal::pin::p11}, GPIOC, GPIO_PIN_11, GPIO_AF8_UART4 },
            {{pal::port::d, pal::pin::p0},  GPIOD, GPIO_PIN_0,  GPIO_AF8_UART4 },
        },
        .txPins = {
            {{pal::port::a, pal::pin::p0},  GPIOA, GPIO_PIN_0,  GPIO_AF8_UART4 },
            {{pal::port::a, pal::pin::p12}, GPIOA, GPIO_PIN_12, GPIO_AF6_UART4 },
            {{pal::port::b, pal::pin::p9}, GPIOB, GPIO_PIN_9, GPIO_AF8_UART4 },
            {{pal::port::c, pal::pin::p10}, GPIOC, GPIO_PIN_10, GPIO_AF8_UART4 },
            {{pal::port::d, pal::pin::p1},  GPIOD, GPIO_PIN_1,  GPIO_AF8_UART4 },
        },
        .rcc = RCC_APB1L(UART4),
        .rxIrq = UART4_IRQn
    },
#endif

#ifdef USE_UART5
    {
        .device = pal::uart::id::u5,
        .reg = UART5,
#ifdef USE_DMA
        .rxDMAChannel = DMA_REQUEST_UART5_RX,
        .rxDMAResource = (dmaResource_t *)UART5_RX_DMA_STREAM,
        .txDMAChannel = DMA_REQUEST_UART5_TX,
        .txDMAResource = (dmaResource_t *)UART5_TX_DMA_STREAM,
#endif
        .rxPins = {
            {{pal::port::b, pal::pin::p6}, GPIOB, GPIO_PIN_6,  GPIO_AF14_UART5 },
            {{pal::port::b, pal::pin::p13}, GPIOB, GPIO_PIN_13, GPIO_AF14_UART5 },
            {{pal::port::c, pal::pin::p12}, GPIOC, GPIO_PIN_12, GPIO_AF8_UART5 },
        },
        .txPins = {
            {{pal::port::b, pal::pin::p5},  GPIOB, GPIO_PIN_5,  GPIO_AF14_UART5 },
            {{pal::port::b, pal::pin::p12}, GPIOB, GPIO_PIN_12, GPIO_AF14_UART5 },
            {{pal::port::c, pal::pin::p11}, GPIOC, GPIO_PIN_11, GPIO_AF8_UART5 },
        },
        .rcc = RCC_APB1L(UART5),
        .rxIrq = UART5_IRQn
    },
#endif

#ifdef USE_UART6
    {
        .device = pal::uart::id::u6,
        .reg = USART6,
#ifdef USE_DMA
        .rxDMAChannel = DMA_REQUEST_USART6_RX,
        .rxDMAResource = (dmaResource_t *)UART6_RX_DMA_STREAM,
        .txDMAChannel = DMA_REQUEST_USART6_TX,
        .txDMAResource = (dmaResource_t *)UART6_TX_DMA_STREAM,
#endif
        .rxPins = {
            { {pal::port::c, pal::pin::p7}, GPIOC, GPIO_PIN_7, GPIO_AF7_USART6 },
            { {pal::port::g, pal::pin::p9}, GPIOG, GPIO_PIN_9, GPIO_AF7_USART6 },
        },
        .txPins = {
            {{pal::port::c, pal::pin::p6}, GPIOC, GPIO_PIN_6, GPIO_AF7_USART6 },
            {{pal::port::g, pal::pin::p14}, GPIOG, GPIO_PIN_14, GPIO_AF7_USART6 }
        },
        .rcc = RCC_APB2(USART6),
        .rxIrq = USART6_IRQn
    },
#endif

#ifdef USE_UART7
    {
        .device = pal::uart::id::u7,
        .reg = UART7,
#ifdef USE_DMA
        .rxDMAChannel = DMA_REQUEST_UART7_RX,
        .rxDMAResource = (dmaResource_t *)UART7_RX_DMA_STREAM,
        .txDMAChannel = DMA_REQUEST_UART7_TX,
        .txDMAResource = (dmaResource_t *)UART7_TX_DMA_STREAM,
#endif
        .rxPins = {
            {{pal::port::a, pal::pin::p8}, GPIOA, GPIO_PIN_8, GPIO_AF11_UART7 },
            {{pal::port::b, pal::pin::p3}, GPIOB, GPIO_PIN_3, GPIO_AF11_UART7 },
            {{pal::port::e, pal::pin::p7}, GPIOE, GPIO_PIN_7, GPIO_AF7_UART7 },
            {{pal::port::f, pal::pin::p6}, GPIOF, GPIO_PIN_6, GPIO_AF7_UART7}
        },
        .txPins = {
            {{pal::port::a, pal::pin::p15}, GPIOA, GPIO_PIN_15, GPIO_AF11_UART7 },
            {{pal::port::b, pal::pin::p4},  GPIOB, GPIO_PIN_4,  GPIO_AF11_UART7 },
            {{pal::port::e, pal::pin::p8},  GPIOE, GPIO_PIN_8,  GPIO_AF7_UART7 },
            {{pal::port::f, pal::pin::p7},  GPIOF, GPIO_PIN_7,  GPIO_AF7_UART7 }
        },
        .rcc = RCC_APB1L(UART7),
        .rxIrq = UART7_IRQn
    },
#endif

#ifdef USE_UART8
    {
        .device = pal::uart::id::u8,
        .reg = UART8,
#ifdef USE_DMA
        .rxDMAChannel = DMA_REQUEST_UART8_RX,
        .rxDMAResource = (dmaResource_t *)UART8_RX_DMA_STREAM,
        .txDMAChannel = DMA_REQUEST_UART8_TX,
        .txDMAResource = (dmaResource_t *)UART8_TX_DMA_STREAM,
#endif
        .rxPins = {
            {{pal::port::e, pal::pin::p0}, GPIOE, GPIO_PIN_0, GPIO_AF8_UART8 },
        },
        .txPins = {
            {{pal::port::e, pal::pin::p1}, GPIOE, GPIO_PIN_1, GPIO_AF8_UART8 }
        },
        .rcc = RCC_APB1L(UART8),
        .rxIrq = UART8_IRQn
    },
#endif

#ifdef USE_UART9
    {
        .device = pal::uart::id::u9,
        .reg = UART9,
#ifdef USE_DMA
        .rxDMAChannel = DMA_REQUEST_UART9_RX,
        .rxDMAResource = (dmaResource_t *)UART9_RX_DMA_STREAM,
        .txDMAChannel = DMA_REQUEST_UART9_TX,
        .txDMAResource = (dmaResource_t *)UART9_TX_DMA_STREAM,
#endif
        .rxPins = {
            {{pal::port::d, pal::pin::p14}, GPIOD, GPIO_PIN_14, GPIO_AF11_UART9 }
        },
        .txPins = {
            {{pal::port::d, pal::pin::p15}, GPIOD, GPIO_PIN_15, GPIO_AF11_UART9 }
        },
        .rcc = RCC_APB2(UART9),
        .rxIrq = UART9_IRQn
    },
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

}};


// Hardware template specialization for retrieving stm32h723 uart hardware details
template <>
template <>
std::optional<const pal::stm32::uart::hw_t*> hardware<pal::stm32::uart::hw_t>::get(pal::uart::id id) {
    return &uartHardware[static_cast<uint8_t>(id)];
}