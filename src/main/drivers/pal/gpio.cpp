#include "gpio.hpp"

pal::gpio::gpio(port port, pin pin)
    : m_port(port), m_pin(pin)
{
}
