#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wuseless-cast"

#include "stm32_dma.hpp"

#include "etl/vector.h"

#include "drivers/rcc.hpp"
#include "drivers/stm32/common/stm32_timer_impl.hpp"
#include "drivers/stm32/common/stm32_dma_impl.hpp"
#include "drivers/stm32/common/stm32_timer.hpp"

#include "drivers/common/hardware.hpp"

static constexpr uint32_t dma_count = static_cast<uint32_t>(pal::dma::id::COUNT);

static etl::vector<pal::dma::id, dma_count> used_dma_idx = {};           // Used hardware dma indexes

static etl::array<uint32_t, 4> tim_cc_ids = {TIM_DMA_CC1, TIM_DMA_CC2, TIM_DMA_CC3, TIM_DMA_CC4};

stm32_dma::stm32_dma(pal::timer_device* timer, uint32_t tim_channel)
    : m_dma_id(pal::dma::id::_1), active(true), m_dma_handle()
{
    // Check if dma is already used
    while (etl::find(used_dma_idx.begin(), used_dma_idx.end(), m_dma_id) != used_dma_idx.end())
    {
        m_dma_id = static_cast<pal::dma::id>(static_cast<uint32_t>(m_dma_id) + 1);
        if (m_dma_id == pal::dma::id::COUNT)
        {
            active = false;
            return;   
        }
    }
    // Mark dma stream as used 
    used_dma_idx.push_back(m_dma_id);

    // Get timer hardware
    const auto& timer_hw = hardware<pal::stm32::timer_hardware_t>::get(timer->get_id());
    const auto& dma_hw = hardware<pal::stm32::dma_hardware_t>::get(m_dma_id);

    // Enable dma clock
    RCC_ClockCmd(dma_hw->rcc, ENABLE);
    
    // Set dma stream
    init_handle();
    m_dma_handle.Instance = dma_hw->stream;
    m_dma_handle.Init.Request = timer_hw->channels[tim_channel].dma_req;

    HAL_DMA_Init(&m_dma_handle);

    // Link dma to timer
    auto& cc_id = tim_cc_ids[tim_channel];

    auto stm32_tim = static_cast<timer_device_stm32*>(timer);
    
    __HAL_LINKDMA(stm32_tim->get_handle(), hdma[cc_id], m_dma_handle);

    // Enable dma interrupt
    // TODO: Enable interrupt
}

stm32_dma::~stm32_dma()
{
    deinit();
}

void stm32_dma::deinit()
{
    if (active)
    {
        auto it = etl::find(used_dma_idx.begin(), used_dma_idx.end(), m_dma_id);
        if (it != used_dma_idx.end())
        {
            used_dma_idx.erase(used_dma_idx.begin() + static_cast<uint32_t>(m_dma_id));
            HAL_DMA_DeInit(&m_dma_handle);
            active = false;
        }
    }
}



constexpr void stm32_dma::init_handle()
{
    m_dma_handle.Init.Direction = DMA_PERIPH_TO_MEMORY;
    m_dma_handle.Init.PeriphInc = DMA_PINC_DISABLE;
    m_dma_handle.Init.MemInc = DMA_MINC_ENABLE;
    m_dma_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    m_dma_handle.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    m_dma_handle.Init.Mode = DMA_CIRCULAR;
    m_dma_handle.Init.Priority = DMA_PRIORITY_HIGH;
    m_dma_handle.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    m_dma_handle.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
    m_dma_handle.Init.MemBurst = DMA_MBURST_SINGLE;
    m_dma_handle.Init.PeriphBurst = DMA_PBURST_SINGLE;
}

#pragma GCC diagnostic pop