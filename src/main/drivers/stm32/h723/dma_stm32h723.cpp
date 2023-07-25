#include "drivers/stm32/common/stm32_dma_impl.hpp"

#include <etl/map.h>

#include "drivers/rcc.hpp"

#include "drivers/common/hardware.hpp"
#include "drivers/pal/dma.hpp"

// Missing stream 0

static const etl::map<pal::dma::id, pal::stm32::dma_hardware_t, pal::stm32::dma_stream_count*2> dma_hw = 
{
    {pal::dma::id::_1,
    {
        .reg = DMA1,
        .rcc = RCC_AHB1(DMA1),
        .stream = DMA1_Stream1,
        .isr = DMA1_Stream1_IRQn
    }},
    {pal::dma::id::_2,
    {
        .reg = DMA1,
        .rcc = RCC_AHB1(DMA1),
        .stream = DMA1_Stream2,
        .isr = DMA1_Stream2_IRQn
    }},
    {pal::dma::id::_3,
    {
        .reg = DMA1,
        .rcc = RCC_AHB1(DMA1),
        .stream = DMA1_Stream3,
        .isr = DMA1_Stream3_IRQn
    }},
    {pal::dma::id::_4,
    {
        .reg = DMA1,
        .rcc = RCC_AHB1(DMA1),
        .stream = DMA1_Stream4,
        .isr = DMA1_Stream4_IRQn
    }},
    {pal::dma::id::_5,
    {
        .reg = DMA1,
        .rcc = RCC_AHB1(DMA1),
        .stream = DMA1_Stream5,
        .isr = DMA1_Stream5_IRQn
    }},
    {pal::dma::id::_6,
    {
        .reg = DMA1,
        .rcc = RCC_AHB1(DMA1),
        .stream = DMA1_Stream6,
        .isr = DMA1_Stream6_IRQn
    }},
    {pal::dma::id::_7,
    {
        .reg = DMA1,
        .rcc = RCC_AHB1(DMA1),
        .stream = DMA1_Stream7,
        .isr = DMA1_Stream7_IRQn
    }},
    {pal::dma::id::_8,
    {
        .reg = DMA2,
        .rcc = RCC_AHB1(DMA2),
        .stream = DMA2_Stream0,
        .isr = DMA2_Stream0_IRQn
    }},
    {pal::dma::id::_9,
    {
        .reg = DMA2,
        .rcc = RCC_AHB1(DMA2),
        .stream = DMA2_Stream1,
        .isr = DMA2_Stream1_IRQn
    }},
    {pal::dma::id::_10,
    {
        .reg = DMA2,
        .rcc = RCC_AHB1(DMA2),
        .stream = DMA2_Stream2,
        .isr = DMA2_Stream2_IRQn
    }},
    {pal::dma::id::_11,
    {
        .reg = DMA2,
        .rcc = RCC_AHB1(DMA2),
        .stream = DMA2_Stream3,
        .isr = DMA2_Stream3_IRQn
    }},
    {pal::dma::id::_12,
    {
        .reg = DMA2,
        .rcc = RCC_AHB1(DMA2),
        .stream = DMA2_Stream4,
        .isr = DMA2_Stream4_IRQn
    }},
    {pal::dma::id::_13,
    {
        .reg = DMA2,
        .rcc = RCC_AHB1(DMA2),
        .stream = DMA2_Stream5,
        .isr = DMA2_Stream5_IRQn
    }},
    {pal::dma::id::_14,
    {
        .reg = DMA2,
        .rcc = RCC_AHB1(DMA2),
        .stream = DMA2_Stream6,
        .isr = DMA2_Stream6_IRQn
    }},
    {pal::dma::id::_15,
    {
        .reg = DMA2,
        .rcc = RCC_AHB1(DMA2),
        .stream = DMA2_Stream7,
        .isr = DMA2_Stream7_IRQn
    }},
    {pal::dma::id::_16,
    {
        .reg = DMA2,
        .rcc = RCC_AHB1(DMA2),
        .stream = DMA2_Stream7,
        .isr = DMA2_Stream7_IRQn
    }}
};


// *******************************************************************************************
// Template specialization for retrieving stm32h723 dma hardware details. Used by hardware.hpp
// *******************************************************************************************
template <>
template <>
const pal::stm32::dma_hardware_t* hardware<pal::stm32::dma_hardware_t>::get(pal::dma::id id) {
    return &dma_hw.at(id);
}


