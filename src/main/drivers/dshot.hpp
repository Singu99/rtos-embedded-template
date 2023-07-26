#pragma once

#include <cstdint>
#include <etl/array.h>

#include "drivers/pal/timer.hpp"
#include "drivers/pal/dma.hpp"

// TODO: Timer device drivers

class dshot{
public:
    enum dshot_speed {
        DSHOT_600 = 600,
        DSHOT_300 = 300,
        DSHOT_150 = 150
    };

    dshot(dshot_speed speed);
    ~dshot() = default;

    void write(uint16_t value);

private:
    uint32_t prepare_packet(uint16_t value);
    void prepare_dma_buffer(uint16_t value);

private:

    // Timer
    pal::timer_device* m_timer;                                 // Timer device for the PWM generation
    pal::timer::channel m_channel;                              // Timer channel for the PWM generation
    dshot_speed m_speed;                                        // Dshot speed

    // DMA
    static constexpr uint32_t MOTOR_BUFFER_SIZE = 18; 
    etl::array<uint32_t,MOTOR_BUFFER_SIZE> m_motor_dma_buffer;             // DMA buffer for the motor PWM duty cycles
    pal::dma_device* m_dma;                                     // DMA device for the PWM generation
};

