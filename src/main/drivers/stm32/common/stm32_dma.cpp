#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wuseless-cast"

#include "stm32_dma.hpp"

#include <etl/vector.h>
#include <etl/map.h>

#include "drivers/pal/isr.hpp"
#include "drivers/rcc.hpp"
#include "drivers/stm32/common/stm32_timer_impl.hpp"
#include "drivers/stm32/common/stm32_dma_impl.hpp"
#include "drivers/stm32/common/stm32_timer.hpp"

#include "drivers/common/hardware.hpp"

#include "error_handler.hpp"

static constexpr uint32_t DMA_DEV_COUNT = static_cast<uint32_t>(pal::dma::id::COUNT);

static etl::array<uint16_t, 4> tim_cc_ids = {TIM_DMA_ID_CC1, TIM_DMA_ID_CC2, TIM_DMA_ID_CC3, TIM_DMA_ID_CC4};

static etl::map<pal::dma::id, DMA_HandleTypeDef*, DMA_DEV_COUNT> dma_handle_table = {};

stm32_dma::stm32_dma()
    : pal::dma_device(), m_dma_handle()
{
    // Get timer hardware
    const auto& dma_hw = hardware<pal::stm32::dma_hardware_t>::get(m_dma_id);

    // Enable dma clock
    RCC_ClockCmd(dma_hw->rcc, ENABLE);
    
    __HAL_RCC_DMA1_CLK_ENABLE();
    __HAL_RCC_DMA2_CLK_ENABLE();

    // Set dma stream
    init_handle();
    m_dma_handle.Instance = dma_hw->stream;

    // Add dma handle to table
    dma_handle_table.insert({m_dma_id, &m_dma_handle});
}

stm32_dma::~stm32_dma()
{
    deinit();
}

void stm32_dma::configure_dma(pal::timer_device *timer, uint32_t tim_channel)
{
    // Get timer hardware
    const auto& timer_hw = hardware<pal::stm32::timer_hardware_t>::get(timer->get_id());

    m_dma_handle.Init.Request = timer_hw->channels[tim_channel].dma_req;
    
    if (HAL_DMA_Init(&m_dma_handle) != HAL_OK)
    {
        error::error_handler();
    }

    // Link dma to timer
    auto cc_id = tim_cc_ids[tim_channel];
    auto stm32_tim = static_cast<timer_device_stm32*>(timer);
    __HAL_LINKDMA(stm32_tim->get_handle(), hdma[cc_id], m_dma_handle);
}

void stm32_dma::enable_irq_impl()
{
    // Get timer hardware
    const auto& dma_hw = hardware<pal::stm32::dma_hardware_t>::get(m_dma_id);
    
    // Enable dma interrupt
    HAL_NVIC_SetPriority(dma_hw->isr, 0, 0);
    HAL_NVIC_EnableIRQ(dma_hw->isr);
}

void stm32_dma::deinit()
{
    if (active)
    {
        HAL_DMA_DeInit(&m_dma_handle);
    }
}


void stm32_dma::init_handle()
{
    m_dma_handle.Init.Direction = DMA_MEMORY_TO_PERIPH;
    m_dma_handle.Init.PeriphInc = DMA_PINC_DISABLE;
    m_dma_handle.Init.MemInc = DMA_MINC_ENABLE;
    m_dma_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    m_dma_handle.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    m_dma_handle.Init.Mode = DMA_NORMAL;
    m_dma_handle.Init.Priority = DMA_PRIORITY_HIGH;
    m_dma_handle.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    m_dma_handle.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
    m_dma_handle.Init.MemBurst = DMA_MBURST_SINGLE;
    m_dma_handle.Init.PeriphBurst = DMA_PBURST_SINGLE;
}

#pragma GCC diagnostic pop

// *****************************************************************************
// Dma IRQ handlers
// *****************************************************************************

extern "C" void DMA1_Stream0_IRQHandler(void)
{
    if (dma_handle_table.find(pal::dma::id::_1) != dma_handle_table.end()) {
        // Configured class instance callback
        isr::get_interrupt_vectors_instance().call<isr::vector_id::DMA1_Stream0_IRQ_HANDLER>();
        // HAL library callback
        HAL_DMA_IRQHandler(dma_handle_table.at(pal::dma::id::_1));
    }
}

extern "C" void DMA1_Stream1_IRQHandler(void)
{
    if (dma_handle_table.find(pal::dma::id::_2) != dma_handle_table.end()) {
        // Configured class instance callback
        isr::get_interrupt_vectors_instance().call<isr::vector_id::DMA1_Stream1_IRQ_HANDLER>();
        // HAL library callback
        HAL_DMA_IRQHandler(dma_handle_table.at(pal::dma::id::_2));
    }
}

extern "C" void DMA1_Stream2_IRQHandler(void)
{
    if (dma_handle_table.find(pal::dma::id::_3) != dma_handle_table.end()) {
        // Configured class instance callback
        isr::get_interrupt_vectors_instance().call<isr::vector_id::DMA1_Stream2_IRQ_HANDLER>();
        // HAL library callback
        HAL_DMA_IRQHandler(dma_handle_table.at(pal::dma::id::_3));
    }
}

extern "C" void DMA1_Stream3_IRQHandler(void)
{
    if (dma_handle_table.find(pal::dma::id::_4) != dma_handle_table.end()) {
        // Configured class instance callback
        isr::get_interrupt_vectors_instance().call<isr::vector_id::DMA1_Stream3_IRQ_HANDLER>();
        // HAL library callback
        HAL_DMA_IRQHandler(dma_handle_table.at(pal::dma::id::_4));
    }
}

extern "C" void DMA1_Stream4_IRQHandler(void)
{
    if (dma_handle_table.find(pal::dma::id::_5) != dma_handle_table.end()) {
        // Configured class instance callback
        isr::get_interrupt_vectors_instance().call<isr::vector_id::DMA1_Stream4_IRQ_HANDLER>();
        // HAL library callback
        HAL_DMA_IRQHandler(dma_handle_table.at(pal::dma::id::_5));
    }
}

extern "C" void DMA1_Stream5_IRQHandler(void)
{
    if (dma_handle_table.find(pal::dma::id::_6) != dma_handle_table.end()) {
        // Configured class instance callback
        isr::get_interrupt_vectors_instance().call<isr::vector_id::DMA1_Stream5_IRQ_HANDLER>();
        // HAL library callback
        HAL_DMA_IRQHandler(dma_handle_table.at(pal::dma::id::_6));
    }
}

extern "C" void DMA1_Stream6_IRQHandler(void)
{
    if (dma_handle_table.find(pal::dma::id::_7) != dma_handle_table.end()) {
        // Configured class instance callback
        isr::get_interrupt_vectors_instance().call<isr::vector_id::DMA1_Stream6_IRQ_HANDLER>();
        // HAL library callback
        HAL_DMA_IRQHandler(dma_handle_table.at(pal::dma::id::_7));
    }
}

extern "C" void DMA1_Stream7_IRQHandler(void)
{
    if (dma_handle_table.find(pal::dma::id::_8) != dma_handle_table.end()) {
        // Configured class instance callback
        isr::get_interrupt_vectors_instance().call<isr::vector_id::DMA1_Stream7_IRQ_HANDLER>();
        // HAL library callback
        HAL_DMA_IRQHandler(dma_handle_table.at(pal::dma::id::_8));
    }
}

extern "C" void DMA2_Stream0_IRQHandler(void)
{
    if (dma_handle_table.find(pal::dma::id::_9) != dma_handle_table.end()) {
        // Configured class instance callback
        isr::get_interrupt_vectors_instance().call<isr::vector_id::DMA2_Stream0_IRQ_HANDLER>();
        // HAL library callback
        HAL_DMA_IRQHandler(dma_handle_table.at(pal::dma::id::_9));
    }
}

extern "C" void DMA2_Stream1_IRQHandler(void)
{
    if (dma_handle_table.find(pal::dma::id::_10) != dma_handle_table.end()) {
        // Configured class instance callback
        isr::get_interrupt_vectors_instance().call<isr::vector_id::DMA2_Stream1_IRQ_HANDLER>();
        // HAL library callback
        HAL_DMA_IRQHandler(dma_handle_table.at(pal::dma::id::_10));
    }
}

extern "C" void DMA2_Stream2_IRQHandler(void)
{
    if (dma_handle_table.find(pal::dma::id::_11) != dma_handle_table.end()) {
        // Configured class instance callback
        isr::get_interrupt_vectors_instance().call<isr::vector_id::DMA2_Stream2_IRQ_HANDLER>();
        // HAL library callback
        HAL_DMA_IRQHandler(dma_handle_table.at(pal::dma::id::_11));
    }
}

extern "C" void DMA2_Stream3_IRQHandler(void)
{
    if (dma_handle_table.find(pal::dma::id::_12) != dma_handle_table.end()) {
        // Configured class instance callback
        isr::get_interrupt_vectors_instance().call<isr::vector_id::DMA2_Stream3_IRQ_HANDLER>();
        // HAL library callback
        HAL_DMA_IRQHandler(dma_handle_table.at(pal::dma::id::_12));
    }
}

extern "C" void DMA2_Stream4_IRQHandler(void)
{
    if (dma_handle_table.find(pal::dma::id::_13) != dma_handle_table.end()) {
        // Configured class instance callback
        isr::get_interrupt_vectors_instance().call<isr::vector_id::DMA2_Stream4_IRQ_HANDLER>();
        // HAL library callback
        HAL_DMA_IRQHandler(dma_handle_table.at(pal::dma::id::_13));
    }
}

extern "C" void DMA2_Stream5_IRQHandler(void)
{
    if (dma_handle_table.find(pal::dma::id::_14) != dma_handle_table.end()) {
        // Configured class instance callback
        isr::get_interrupt_vectors_instance().call<isr::vector_id::DMA2_Stream5_IRQ_HANDLER>();
        // HAL library callback
        HAL_DMA_IRQHandler(dma_handle_table.at(pal::dma::id::_14));
    }
}

extern "C" void DMA2_Stream6_IRQHandler(void)
{
    if (dma_handle_table.find(pal::dma::id::_15) != dma_handle_table.end()) {
        // Configured class instance callback
        isr::get_interrupt_vectors_instance().call<isr::vector_id::DMA2_Stream6_IRQ_HANDLER>();
        // HAL library callback
        HAL_DMA_IRQHandler(dma_handle_table.at(pal::dma::id::_15));
    }
}

extern "C" void DMA2_Stream7_IRQHandler(void)
{
    if (dma_handle_table.find(pal::dma::id::_16) != dma_handle_table.end()) {
        // Configured class instance callback
        isr::get_interrupt_vectors_instance().call<isr::vector_id::DMA2_Stream7_IRQ_HANDLER>();
        // HAL library callback
        HAL_DMA_IRQHandler(dma_handle_table.at(pal::dma::id::_16));
    }
}

