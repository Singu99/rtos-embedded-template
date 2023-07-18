#pragma once

#include "drivers/pal/uart.hpp"
#include "drivers/pal/global_io.hpp"

#include <etl/array.h>

/* TODO: This should move to config folder on source in the future */
/* THIS HEADER SHOULD ONLY BE INCLUDED IN CONFIG */

namespace board_config {

    /* ******** Should be stored in rom - Start ******** */
    constexpr pal::uart::id rx_uart_id = pal::uart::id::u1;

    /* ******** Should be stored in rom - End ******** */



    // Tables defining the configuration of the system
    /* ******** Board configurations specifics - Start ******** */
    struct uart_config {
        pal::uart::id id;
        pal::io_id tx_pin;       // Use different gpio class, e.g gpio_def...
        pal::io_id rx_pin;       
    };

    // KONEXH723 uart configuration. This should not be in rom
    const etl::array<uart_config, 9> uart_config_map = {{
        {
            .id = pal::uart::id::u1, 
            .tx_pin = { pal::port::B, pal::pin::_14 }, 
            .rx_pin = { pal::port::B, pal::pin::_15 },
        },
        {
            .id = pal::uart::id::u2, 
            .tx_pin = { pal::port::A, pal::pin::_2 }, 
            .rx_pin = { pal::port::A, pal::pin::_3 },
        },
        {
            .id = pal::uart::id::unknown, 
            .tx_pin = { pal::port::D, pal::pin::_0 }, 
            .rx_pin = { pal::port::D, pal::pin::_1 },
        },
        {
            .id = pal::uart::id::u4, 
            .tx_pin = { pal::port::A, pal::pin::_0 }, 
            .rx_pin = { pal::port::A, pal::pin::_1 },
        },
        {
            .id = pal::uart::id::unknown, 
            .tx_pin = { pal::port::D, pal::pin::_0 }, 
            .rx_pin = { pal::port::D, pal::pin::_1 },
        },
        {
            .id = pal::uart::id::u6, 
            .tx_pin = { pal::port::D, pal::pin::_6 }, 
            .rx_pin = { pal::port::D, pal::pin::_7 },
        },
        {
            .id = pal::uart::id::u7, 
            .tx_pin = { pal::port::E, pal::pin::_8 }, 
            .rx_pin = { pal::port::E, pal::pin::_7 },
        },
        {
            .id = pal::uart::id::u8, 
            .tx_pin = { pal::port::E, pal::pin::_1 }, 
            .rx_pin = { pal::port::E, pal::pin::_0 },
        },
        {
            .id = pal::uart::id::u9, 
            .tx_pin = { pal::port::D, pal::pin::_15 }, 
            .rx_pin = { pal::port::D, pal::pin::_14 },
        }
    }};


    const etl::array<pal::io_id, 4> motor_config_map = {{
        { pal::port::E, pal::pin::_9 },
        { pal::port::E, pal::pin::_11 },
        { pal::port::E, pal::pin::_13 },
        { pal::port::E, pal::pin::_14 }
    }};

    const etl::array<pal::io_id, 2> led_config_map = {{
        { pal::port::E, pal::pin::_2 },
        { pal::port::E, pal::pin::_4 }
    }};

    const etl::array<pal::io_id, 3> spi_config_map = {{
        { pal::port::A, pal::pin::_5 },
        { pal::port::A, pal::pin::_6 },
        { pal::port::A, pal::pin::_7 }
    }};


    /* ******** Board configurations specifics - End ******** */

};  // namespace board_config

