#pragma once

#include "etl/delegate_service.h"

namespace isr {

    // Define the high level interrupt vector ids of the system
    enum vector_id : uint32_t
    {  
        TIM1_CC_IRQ_HANDLER = 42,  
        TIM2_IRQ_HANDLER    = 43,  
        TIM3_IRQ_HANDLER    = 44,  
        UART1_IRQ_HANDLER  = 52,  
        UART2_IRQ_HANDLER  = 53,
        UART3_IRQ_HANDLER  = 54,
        UART4_IRQ_HANDLER  = 55,
        UART5_IRQ_HANDLER  = 56,
        UART6_IRQ_HANDLER  = 57,
        UART7_IRQ_HANDLER  = 58,
        UART8_IRQ_HANDLER  = 59,
        UART9_IRQ_HANDLER   = 60,
        VECTOR_ID_END,  
        VECTOR_ID_OFFSET    =  TIM1_CC_IRQ_HANDLER,
        VECTOR_ID_RANGE     = VECTOR_ID_END - VECTOR_ID_OFFSET
    };

    using isr_vectors = etl::delegate_service<VECTOR_ID_RANGE, VECTOR_ID_OFFSET>;
    isr_vectors& get_interrupt_vectors_instance();

}