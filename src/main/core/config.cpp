#include "config.hpp"
#include "board_config.hpp"         // Tables defining the configuration of the system








namespace config {

    /* Interface for retreiving configuration data */
    pal::uart::id rx::get_rx_uart_id()
    {
        return board_config::rx_uart_id;
    }

    pal::io_id rx::get_uart_rx_io(pal::uart::id uart_id)
    {
        return board_config::uart_config_map[static_cast<uint32_t>(uart_id)].rx_pin;
    }

    pal::io_id rx::get_uart_tx_io(pal::uart::id uart_id)
    {
        return board_config::uart_config_map[static_cast<uint32_t>(uart_id)].tx_pin;
    }


    // Complete usless hardcoded. Need to be refactored
    pal::io_id motor::get_timer_channel_io_id(pal::timer::id t_id, pal::timer::channel t_channel)
    {
        if (t_id == pal::timer::id::t1)
        {
            switch (t_channel)
            {
            case pal::timer::channel::ch1:
                return pal::io_id(pal::port::E, pal::pin::_9);
                break;
            case pal::timer::channel::ch2:
                return pal::io_id(pal::port::E, pal::pin::_11);
                break;
            case pal::timer::channel::ch3:
                return pal::io_id(pal::port::E, pal::pin::_13);
                break;
            case pal::timer::channel::ch4:
                return pal::io_id(pal::port::E, pal::pin::_14);
                break;
            default:
                break;
            }
        }
        return pal::io_id();
    }
}


