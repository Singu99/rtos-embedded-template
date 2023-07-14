#include "config.hpp"


// Tables defining the configuration of the system









/* Think about a better way to abstract this */
pal::uart::id config::rx::get_rx_uart_id()
{
    return pal::uart::id();
}

pal::gpio config::rx::get_uart_rx_pin(pal::uart::id uart_id)
{
    return pal::gpio(pal::port::id::a, 10);
}

pal::gpio config::rx::get_uart_tx_pin(pal::uart::id uart_id)
{
    return pal::gpio();
}
