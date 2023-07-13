#pragma once

#include "drivers/pal/uart.hpp"

/**
 * @brief Class used to get the configuration of the system (communications, gpio, etc)
*/
namespace config {


    // Used to retrieve the configuration of the serial rx
    class rx {
        
        static pal::uart::id get_rx_usart_id(); 


    private:
        rx() = delete;
        ~rx() = delete;
    };











}; // namespace config
