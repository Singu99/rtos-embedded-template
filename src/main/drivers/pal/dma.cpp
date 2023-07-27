#include "dma.hpp"

#include <etl/vector.h>
#include <etl/delegate_service.h>

#include "target/target.h"

#include "drivers/stm32/common/stm32_dma.hpp"

#include "drivers/pal/isr.hpp"

static constexpr uint32_t dma_count = static_cast<uint32_t>(pal::dma::id::COUNT);

/* **** Architectures Start **** */
#ifdef STM32
// Forward declaration of hardware specific class
#include "drivers/stm32/common/stm32_timer.hpp"
#define dma_device_hw stm32_dma
#elif ESP32
#include "drivers/esp32/common/uart_esp32.hpp"
#else
#error "No architecture defined"
#endif

static etl::vector<pal::dma::id, dma_count> used_dma_idx = {};                      // Used hardware dma indexes
static etl::vector<dma_device_hw, dma_count> dma_devices;                           // Dma devices

namespace pal {

    // irq vector ids
    static const etl::array<isr::vector_id, 16> vector_ids = {
        isr::vector_id::DMA1_Stream0_IRQ_HANDLER,
        isr::vector_id::DMA1_Stream1_IRQ_HANDLER,
        isr::vector_id::DMA1_Stream2_IRQ_HANDLER,
        isr::vector_id::DMA1_Stream3_IRQ_HANDLER,
        isr::vector_id::DMA1_Stream4_IRQ_HANDLER,
        isr::vector_id::DMA1_Stream5_IRQ_HANDLER,
        isr::vector_id::DMA1_Stream6_IRQ_HANDLER,
        isr::vector_id::DMA1_Stream7_IRQ_HANDLER,
        isr::vector_id::DMA2_Stream0_IRQ_HANDLER,
        isr::vector_id::DMA2_Stream1_IRQ_HANDLER,
        isr::vector_id::DMA2_Stream2_IRQ_HANDLER,
        isr::vector_id::DMA2_Stream3_IRQ_HANDLER,
        isr::vector_id::DMA2_Stream4_IRQ_HANDLER,
        isr::vector_id::DMA2_Stream5_IRQ_HANDLER,
        isr::vector_id::DMA2_Stream6_IRQ_HANDLER,
        isr::vector_id::DMA2_Stream7_IRQ_HANDLER
    };


    dma_device::dma_device()
        : active(true)
    {
        // Check if dma is already used
        while (etl::find(used_dma_idx.begin(), used_dma_idx.end(), m_dma_id) != used_dma_idx.end())
        {
            m_dma_id = static_cast<dma::id>(static_cast<uint32_t>(m_dma_id) + 1);
            if (m_dma_id == dma::id::COUNT)
            {
                active = false;
                return;   
            }
        }
        // Mark dma stream as used 
        used_dma_idx.push_back(m_dma_id);
    }

    dma_device::~dma_device()
    {
        deinit();   
    }

    void dma_device::enable_irq(etl::delegate<void(size_t)> callback)
    {
        // Register uart interrupt
        uint32_t device_id = static_cast<uint32_t>(m_dma_id);

        // The callback could be improved using a method to generate the apropriate callback
        isr::get_interrupt_vectors_instance().register_delegate(vector_ids[device_id], callback);

        // Enable hardawre dependent interrupt
        enable_irq_impl();
    }

    void dma_device::deinit()
    {
        if (active)
        {
            auto it = etl::find(used_dma_idx.begin(), used_dma_idx.end(), m_dma_id);
            if (it != used_dma_idx.end())
            {
                used_dma_idx.erase(used_dma_idx.begin() + static_cast<uint32_t>(m_dma_id));
            }
        }
    }

}

// ***********************************************************************************
// Template speciallizations for getting devices specific instances. Used by device.hpp.
// ***********************************************************************************
/**
 * @brief Get dma device instance that will work with the given timer device.
 */
template<>
pal::dma_device* device::get<pal::dma_device>(pal::timer::id dev_id)
{
    (void)dev_id;                       // Unused
    dma_devices.emplace_back();         // Will automatically allocate an unused dma stream
    // If the intend is to use the same stream for multiple purpusoes, then the instance can be reused this instance
    return &dma_devices.back();
}


/**
 * TODO: 
 * Missing method for erasing/releasing devices
 */
