#include "gpio.hpp"

pal::gpio::gpio()
    : m_port(port::unknown), m_pin(pin::unknown)
{
}

pal::gpio::gpio(port port, pin pin)
    : m_port(port), m_pin(pin)
{
}
