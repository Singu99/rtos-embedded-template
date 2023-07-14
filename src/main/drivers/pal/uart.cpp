#include <array>

#include "uart.hpp"


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

    std::optional<uart_device*> uart_device::claim_device(uart::id dev_id, io::resource_id claimer)
    {
        // Actual hardware instances 
        static std::array<uart_device_hw, 9> uart_devices = {{
            uart_device_hw(uart::id::u1),
            uart_device_hw(uart::id::u2),
            uart_device_hw(uart::id::u3),
            uart_device_hw(uart::id::u4),
            uart_device_hw(uart::id::u5),
            uart_device_hw(uart::id::u6),
            uart_device_hw(uart::id::u7),
            uart_device_hw(uart::id::u8),
            uart_device_hw(uart::id::u9)
        }};

        uart_device* device = &uart_devices[static_cast<int>(dev_id)];

        if (device->m_claimer == io::resource_id::FREE || device->m_claimer == claimer) {
            device->m_claimer = claimer;
            return device;
        } 
        return {};
    }

    bool uart_device::release_device(uart_device* device, io::resource_id claimer)
    {
        if (device != nullptr && device->m_claimer == claimer) {
            device->m_claimer = io::resource_id::FREE;
            return true;
        }
        return false;
    }

    uart_device::uart_device(uart::id dev_id)
        : m_dev_id(dev_id), m_claimer(io::resource_id::FREE) {}


    /* Interrupts */
    uart_interruptable* uart_interruptable::null_interrupt()
    {
        class null_interrupt : public uart_interruptable {
        public:
            void on_rx_interrupt() override {}
            void on_tx_interrupt() override {}
        };

        static null_interrupt null_interrupt;
        return &null_interrupt;
    }

}   // namespace pal

