#include "dshot.hpp"

#define MOTOR_BIT_1 687/2
#define MOTOR_BIT_0 343/2

dshot::dshot(dshot_speed speed)
{
	// unused for now
	(void)speed;

	// prepere zero throttle packet
	prepare_dma_buffer(0);

	m_timer = device::claim_device<pal::timer_device>(pal::timer::id::t1, io::resource_id::MOTOR1);
    m_dma = device::claim_device<pal::dma_device>(pal::timer::id::t1, io::resource_id::MOTOR1);

    static constexpr auto tim_channel = static_cast<uint32_t>(pal::timer::channel::ch1);
    m_dma->configure_dma(m_timer, tim_channel);

    m_timer->configure_pwm(0, 917/2, pal::timer::channel::ch1);

    // Start the timer
    auto buffer = etl::span<uint32_t>(m_motor_dma_buffer);
    m_timer->start_pwm(pal::timer::channel::ch1, buffer);
}

void dshot::write(uint16_t value)
{
   // Value should be between 0 and 2047
    if(value > 2047)
    {
         value = 2047;
    }

    prepare_dma_buffer(value);
}

uint32_t dshot::prepare_packet(uint16_t value)
{
    uint16_t packet;
	bool dshot_telemetry = false;

	packet = (value << 1) | (dshot_telemetry ? 1 : 0);

	// compute checksum
	unsigned csum = 0;
	unsigned csum_data = packet;

	for(int i = 0; i < 3; i++)
	{
        csum ^=  csum_data; // xor data by nibbles
        csum_data >>= 4;
	}

	csum &= 0xf;
	packet = (packet << 4) | csum;

	return packet;
}

void dshot::prepare_dma_buffer(uint16_t value)
{
    uint16_t packet;
	packet = prepare_packet(value);

	for(uint32_t i = 0; i < MOTOR_BUFFER_SIZE-2; i++)
	{
		m_motor_dma_buffer[i] = (packet & 0x8000) ? MOTOR_BIT_1 : MOTOR_BIT_0;
		packet <<= 1;
	}

	m_motor_dma_buffer[MOTOR_BUFFER_SIZE-2] = 0;
	m_motor_dma_buffer[MOTOR_BUFFER_SIZE-1] = 0;
}
