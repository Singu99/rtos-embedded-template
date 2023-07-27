#pragma once

#include "etl/delegate_service.h"

namespace isr {

    // Define the high level interrupt vector ids of the system
    enum vector_id : uint32_t
    {  
        TIM1_IRQ_HANDLER   = 42,  
        TIM2_IRQ_HANDLER   = 43,  
        TIM3_IRQ_HANDLER   = 44,
        TIM4_IRQ_HANDLER   = 45,
        TIM5_IRQ_HANDLER   = 46,
        TIM6_IRQ_HANDLER   = 47,
        TIM7_IRQ_HANDLER   = 48,  
        TIM8_IRQ_HANDLER   = 49,
        TIM9_IRQ_HANDLER   = 50,
        TIM10_IRQ_HANDLER  = 51,
        TIM11_IRQ_HANDLER  = 52,
        TIM12_IRQ_HANDLER  = 53,
        TIM13_IRQ_HANDLER  = 54,
        TIM14_IRQ_HANDLER  = 55,
        TIM15_IRQ_HANDLER  = 56,
        TIM16_IRQ_HANDLER  = 57,
        TIM17_IRQ_HANDLER  = 58,  
        UART1_IRQ_HANDLER  = 60,  
        UART2_IRQ_HANDLER  = 61,
        UART3_IRQ_HANDLER  = 62,
        UART4_IRQ_HANDLER  = 63,
        UART5_IRQ_HANDLER  = 64,
        UART6_IRQ_HANDLER  = 65,
        UART7_IRQ_HANDLER  = 66,
        UART8_IRQ_HANDLER  = 67,
        UART9_IRQ_HANDLER  = 68,
        DMA1_Stream0_IRQ_HANDLER = 69,
        DMA1_Stream1_IRQ_HANDLER = 70,
        DMA1_Stream2_IRQ_HANDLER = 71,
        DMA1_Stream3_IRQ_HANDLER = 72,
        DMA1_Stream4_IRQ_HANDLER = 73,
        DMA1_Stream5_IRQ_HANDLER = 74,
        DMA1_Stream6_IRQ_HANDLER = 75,
        DMA1_Stream7_IRQ_HANDLER = 76,
        DMA2_Stream0_IRQ_HANDLER = 77,
        DMA2_Stream1_IRQ_HANDLER = 78,
        DMA2_Stream2_IRQ_HANDLER = 79,
        DMA2_Stream3_IRQ_HANDLER = 80,
        DMA2_Stream4_IRQ_HANDLER = 81,
        DMA2_Stream5_IRQ_HANDLER = 82,
        DMA2_Stream6_IRQ_HANDLER = 83,
        DMA2_Stream7_IRQ_HANDLER = 84,
        VECTOR_ID_END,  
        VECTOR_ID_OFFSET    =  TIM1_IRQ_HANDLER,
        VECTOR_ID_RANGE     = VECTOR_ID_END - VECTOR_ID_OFFSET
    };

    using isr_vectors = etl::delegate_service<VECTOR_ID_RANGE, VECTOR_ID_OFFSET>;
    isr_vectors& get_interrupt_vectors_instance();

}