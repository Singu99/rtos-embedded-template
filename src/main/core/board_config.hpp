#pragma once

#include "drivers/pal/uart.hpp"
#include "drivers/pal/gpio.hpp"

#include <array>

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
        pal::gpio tx_pin;       // Use different gpio class, e.g gpio_def...
        pal::gpio rx_pin;       
    };

    // KONEXH723 uart configuration. This should not be in rom
    const std::array<uart_config, 9> uart_config_map = {{
        {
            .id = pal::uart::id::u1, 
            .tx_pin = { pal::port::b, pal::pin::p14 }, 
            .rx_pin = { pal::port::b, pal::pin::p15 },
        },
        {
            .id = pal::uart::id::u2, 
            .tx_pin = { pal::port::a, pal::pin::p2 }, 
            .rx_pin = { pal::port::a, pal::pin::p3 },
        },
        {
            .id = pal::uart::id::unknown, 
            .tx_pin = { pal::port::d, pal::pin::p0 }, 
            .rx_pin = { pal::port::d, pal::pin::p1 },
        },
        {
            .id = pal::uart::id::u4, 
            .tx_pin = { pal::port::a, pal::pin::p0 }, 
            .rx_pin = { pal::port::a, pal::pin::p1 },
        },
        {
            .id = pal::uart::id::unknown, 
            .tx_pin = { pal::port::d, pal::pin::p0 }, 
            .rx_pin = { pal::port::d, pal::pin::p1 },
        },
        {
            .id = pal::uart::id::u6, 
            .tx_pin = { pal::port::c, pal::pin::p6 }, 
            .rx_pin = { pal::port::c, pal::pin::p7 },
        },
        {
            .id = pal::uart::id::u7, 
            .tx_pin = { pal::port::e, pal::pin::p8 }, 
            .rx_pin = { pal::port::e, pal::pin::p7 },
        },
        {
            .id = pal::uart::id::u8, 
            .tx_pin = { pal::port::e, pal::pin::p1 }, 
            .rx_pin = { pal::port::e, pal::pin::p0 },
        },
        {
            .id = pal::uart::id::u9, 
            .tx_pin = { pal::port::d, pal::pin::p15 }, 
            .rx_pin = { pal::port::d, pal::pin::p14 },
        }
    }};


    const std::array<pal::gpio, 4> motor_config_map = {{
        { pal::port::e, pal::pin::p9 },
        { pal::port::e, pal::pin::p11 },
        { pal::port::e, pal::pin::p13 },
        { pal::port::e, pal::pin::p14 }
    }};

    const std::array<pal::gpio, 2> led_config_map = {{
        { pal::port::d, pal::pin::p2 },
        { pal::port::d, pal::pin::p4 }
    }};

    const std::array<pal::gpio, 3> spi_config_map = {{
        { pal::port::a, pal::pin::p5 },
        { pal::port::a, pal::pin::p6 },
        { pal::port::a, pal::pin::p7 }
    }};


    /* ******** Board configurations specifics - End ******** */

};  // namespace board_config

