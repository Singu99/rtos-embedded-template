#pragma once

#include "drivers/platform.hpp"

namespace pal {


    namespace stm32
    {
        static constexpr uint32_t dma_stream_count = 8;

        struct dma_hardware_t
        {
            DMA_TypeDef* reg;
            uint32_t rcc;
            DMA_Stream_TypeDef* stream;
            IRQn_Type isr;
        };

    }



}

