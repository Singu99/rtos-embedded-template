#pragma once

#include "etl/vector.h"
#include "drivers/pal/uart.hpp"
#include "drivers/pal/timer.hpp"

namespace pal {

    enum class port {
        A = 0, B, C, D, E, F, G, H, I, J, K, COUNT
    };

    enum class pin {
        _0 = 0, _1, _2, _3, _4, _5, _6, _7, _8, _9,
        _10, _11, _12, _13, _14, _15, COUNT
    };

    struct io_id {
        port port_id;
        pin pin_id;

        // Operator equals 
        bool operator==(const io_id& other) const
        {
            return (port_id == other.port_id) && (pin_id == other.pin_id);
        }
    };


    class global_io {
    public:
        global_io() = default;

        // Uart pin configuration
        static void configure_pin(uart::id uart_id, io_id io);

        // Timer pin configuration
        static void configure_pin(timer::id timer_id, pal::timer::channel channel, io_id io);
        
        // Rest of pin configurations
        // ....

        static constexpr uint32_t io_count = static_cast<uint32_t>(pin::COUNT) * static_cast<uint32_t>(port::COUNT);
    private:
        

    };


}
