#pragma once

#include <optional>
#include <span>
#include <cstdint>

#include "target/target.h"

#include "drivers/pal/gpio.hpp"

#include "io/resource.hpp"


// ...

/* **** Architectures End **** */

namespace pal {

    namespace uart {
        enum class id { u1 = 0, u2, u3, u4, u5, u6, u7, u8, u9 };
        enum class bus { full_duplex = 0, half_duplex };
        enum class mode { tx = 0, rx, tx_rx };
        enum class status { ok = 0, error, busy, timeout, not_supported, not_opened };
    }

    // Interface for handling usart interrupts
    class uart_interruptable {
    public:
        // Interface
        virtual void on_rx_interrupt() = 0;
        virtual void on_tx_interrupt() = 0;

        static uart_interruptable* null_interrupt();

    };

    /**
     * @brief: Base class for all UART hardware implementations
     */ 
    class uart_device {
    public:

        static std::optional<uart_device*> claim_device(uart::id dev_id, io::resource_id claimer);
        static bool release_device(uart_device* device, io::resource_id claimer);

        virtual void open(uart::bus bus, uart::mode mode, uint32_t baudrate, uart_interruptable* rsi = nullptr) = 0;                // Open for send and interrupt         
        virtual void close() = 0;

        template<typename T>
        inline uart::status send(std::span<T> buffer) { return send(buffer.data(), buffer.size()); }

        template<typename T>
        inline uart::status send_nonblocking(std::span<T> buffer, bool recursive = false) { return send_nonblocking(buffer.data(), buffer.size(), recursive); }

        template<typename T>
        inline uart::status receive(std::span<T> buffer) { return receive(buffer.data(), buffer.size()); }

        template<typename T>
        inline uart::status receive_nonblocking(std::span<T> buffer, bool recursive = false) { return receive_nonblocking(buffer.data(), buffer.size(), recursive); }

    protected:
        uart_device(uart::id dev_id);                                               // for now
        ~uart_device() = default;                                                   // for now
    
        virtual uart::status send(void* buffer, uint32_t size) = 0;
        virtual uart::status send_nonblocking(void* buffer, uint32_t size, bool recursive = false) = 0;
        virtual uart::status receive(void* buffer, uint32_t size) = 0;
        virtual uart::status receive_nonblocking(void* buffer, uint32_t size, bool recursive = false) = 0;
    private:
        uart::id m_dev_id;                                                          // Keep track of which device this is
        io::resource_id m_claimer;                                                  // Keep track of who is using this device

    };

}