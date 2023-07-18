#include "config.hpp"
#include "board_config.hpp"         // Tables defining the configuration of the system








namespace config {

    /* Interface for retreiving configuration data */
    inline pal::uart::id rx::get_rx_uart_id()
    {
        return board_config::rx_uart_id;
    }

    inline pal::gpio rx::get_uart_rx_pin(pal::uart::id uart_id)
    {
        return board_config::uart_config_map[static_cast<uint32_t>(uart_id)].rx_pin;
    }

    inline pal::gpio rx::get_uart_tx_pin(pal::uart::id uart_id)
    {
        return board_config::uart_config_map[static_cast<uint32_t>(uart_id)].tx_pin;
    }

}


