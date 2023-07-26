#pragma once

#include "drivers/pal/uart.hpp"
#include "drivers/pal/global_io.hpp"

/**
 * @brief Class used to get the configuration of the system (communications, gpio, etc). THis informations should be stored in rom (modified by configurator)
*/
namespace config {


    // Used to retrieve the configuration of the serial rx
    class rx {
    public:
        static pal::uart::id get_rx_uart_id(); 
        static pal::io_id get_uart_rx_io(pal::uart::id uart_id);
        static pal::io_id get_uart_tx_io(pal::uart::id uart_id);


    };

    class motor {
    public:
    
        static pal::io_id get_timer_channel_io_id(pal::timer::id t_id, pal::timer::channel t_channel);

    };

}; // namespace config
