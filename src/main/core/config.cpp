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

}


