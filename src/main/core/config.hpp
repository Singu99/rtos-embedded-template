#pragma once

#include "drivers/pal/uart.hpp"
#include "drivers/pal/gpio.hpp"

/**
 * @brief Class used to get the configuration of the system (communications, gpio, etc). THis informations should be stored in rom (modified by configurator)
*/
namespace config {


    // Used to retrieve the configuration of the serial rx
    class rx {
        
        static pal::uart::id get_rx_uart_id(); 
        static pal::gpio get_uart_rx_pin(pal::uart::id uart_id);
        static pal::gpio get_uart_tx_pin(pal::uart::id uart_id);

    private:
        rx() = delete;
        ~rx() = delete;
    };











}; // namespace config
