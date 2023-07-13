#include "config.hpp"

// Hard coded for now. This should be read from rom configuration.
pal::uart::id config::rx::get_rx_usart_id()
{
    return pal::uart::id::u1;
}
