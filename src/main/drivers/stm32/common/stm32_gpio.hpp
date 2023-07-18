#pragma once

#include "drivers/pal/gpio.hpp"

class stm32_gpio : public pal::gpio {

public:
    stm32_gpio(pal::port port, pal::pin pin);
    ~stm32_gpio() = default;

    // Custom init functions... (peripheral, etc...)

    void set() override;
    void reset() override;
    void toggle() override;
    bool read() override;

};