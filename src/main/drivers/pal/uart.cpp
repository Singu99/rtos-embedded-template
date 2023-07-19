#include <etl/array.h>

#include "uart.hpp"
#include "isr.hpp"

/* **** Architectures Start **** */
#ifdef STM32
// Forward declaration of hardware specific class
#include "drivers/stm32/common/stm32_uart.hpp"
#define uart_device_hw uart_device_stm32
#elif ESP32
#include "drivers/esp32/common/uart_esp32.hpp"
#else
#error "No architecture defined"
#endif


namespace pal {

    constexpr etl::array<isr::vector_id, 9> vector_ids = {
        isr::vector_id::UART1_IRQ_HANDLER,
        isr::vector_id::UART2_IRQ_HANDLER,
        isr::vector_id::UART3_IRQ_HANDLER,
        isr::vector_id::UART4_IRQ_HANDLER,
        isr::vector_id::UART5_IRQ_HANDLER,
        isr::vector_id::UART6_IRQ_HANDLER,
        isr::vector_id::UART7_IRQ_HANDLER,
        isr::vector_id::UART8_IRQ_HANDLER,
        isr::vector_id::UART9_IRQ_HANDLER
    };

    uart::status uart_device::open(uart::bus_comm com, uart::mode mode, uint32_t baudrate, etl::delegate<void(size_t)> callback)
    {
        // Register uart interrupt
        uint32_t device_id = static_cast<uint32_t>(m_dev_id);

        // The callback could be improved using a method to generate the apropriate callback
        isr::get_interrupt_vectors_instance().register_delegate(vector_ids[device_id], callback);

        // Open hardware specific uart
        return open(com, mode, baudrate);
    }

    uart_device::uart_device(uart::id dev_id)
        : device(), m_dev_id(dev_id) {}


}   // namespace pal


// ***********************************************************************************
// Template speciallization for getting devices specific instances. Used by device.hpp
// ***********************************************************************************
template<>
pal::uart_device* device::get<pal::uart_device>(pal::uart::id dev_id)
{
    static etl::array<uart_device_hw, 9> uart_devices = {{
        { uart_device_hw(pal::uart::id::u1)},
        { uart_device_hw(pal::uart::id::u2)},
        { uart_device_hw(pal::uart::id::u3)},
        { uart_device_hw(pal::uart::id::u4)},
        { uart_device_hw(pal::uart::id::u5)},
        { uart_device_hw(pal::uart::id::u6)},
        { uart_device_hw(pal::uart::id::u7)},
        { uart_device_hw(pal::uart::id::u8)},
        { uart_device_hw(pal::uart::id::u9)}
    }};

    return &uart_devices[static_cast<uint32_t>(dev_id)];
}
