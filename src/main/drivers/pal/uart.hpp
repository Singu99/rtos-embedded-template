#pragma once

#include <optional>
#include <span>
#include <cstdint>

#include "target/target.h"

#include "drivers/common/device.hpp"

#include "io/resource.hpp"

#include <etl/delegate_service.h>
#include <etl/delegate.h>

// ...

/* **** Architectures End **** */

namespace pal {

    namespace uart {
        enum class id { u1 = 0, u2, u3, u4, u5, u6, u7, u8, u9, unknown, count };
        enum class bus_comm { full_duplex = 0, half_duplex, count };
        enum class mode { tx = 0, rx, tx_rx, count };
        enum class status { ok = 0, error, busy, timeout, not_supported, not_opened, count };
    }

    /**
     * @brief: Base class for all UART hardware implementations
     */ 
    class uart_device : public device {
    public:
        uart::status open(uart::bus_comm com, uart::mode mode, uint32_t baudrate, etl::delegate<void(size_t)> callback);     
        virtual void close() = 0;

        template<typename T>
        inline uart::status send(std::span<T> buffer) { return send(buffer.data(), buffer.size()); }

        template<typename T>
        inline uart::status send_nonblocking(std::span<T> buffer, bool recursive = false) { return send_nonblocking(buffer.data(), buffer.size(), recursive); }

        template<typename T>
        inline uart::status receive(std::span<T> buffer) { return receive(buffer.data(), buffer.size()); }

        template<typename T>
        inline uart::status receive_nonblocking(std::span<T> buffer, bool recursive = true) { return receive_nonblocking(buffer.data(), buffer.size(), recursive); }

        // Public for now. Refactor later
        uart_device(uart::id dev_id);                                               // for now
        ~uart_device() = default;                                                   // for now
    protected:
        
        // ************************************************************
        // Uart hardware specific interface
        // ************************************************************
        virtual uart::status open(uart::bus_comm com, uart::mode mode, uint32_t baudrate) = 0;

        virtual uart::status send(void* buffer, uint32_t size) = 0;
        virtual uart::status send_nonblocking(void* buffer, uint32_t size, bool recursive) = 0;
        virtual uart::status receive(void* buffer, uint32_t size) = 0;
        virtual uart::status receive_nonblocking(void* buffer, uint32_t size, bool recursive) = 0;
    protected:
        uart::id m_dev_id;                                                          // Keep track of which device this is
        
    };

}