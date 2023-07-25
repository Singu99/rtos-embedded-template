#pragma once

#include "drivers/platform.hpp"
#include "drivers/pal/dma.hpp"
#include "drivers/pal/timer.hpp"

#include <etl/span.h>

class stm32_dma
{
public:
    // Constructor for dma used by timer
    stm32_dma(pal::timer_device* timer, uint32_t tim_channel);

    // Constructor for dma used by uart
    // ...

    ~stm32_dma();    

private:

    constexpr void init_handle();

    void deinit();

private:
    pal::dma::id m_dma_id;
    bool active; 

    DMA_HandleTypeDef m_dma_handle;
    /* data */
};
