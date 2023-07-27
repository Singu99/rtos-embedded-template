#include "dshot.hpp"


#define MOTOR_BIT_1 308
#define MOTOR_BIT_0 308/2

using routine = etl::delegate<void(size_t)>;

/**
 * What's happening now is that since the last bit is zero when the dma transfer is completeated it just sends zeros.
 * Then whe update again the dma buffer and restart the transger. The problem is that the timer is still running and 
 * and that can cause the first bit to get lost. 
 * Known issue: Since we start the pwm 
 * 
*/


/**
 * Idea is to start timer pwm on write. Activate dma irq. On the dma irq stop the timer pwm.
*/
dshot::dshot(dshot_speed speed)
	: m_motor_dma_buffer(), m_buffer(m_motor_dma_buffer)
{
	// unused for now
	(void)speed;

	// prepere zero throttle packet
	prepare_dma_buffer(0);

	// Claim required devices
	m_timer = device::claim_device<pal::timer_device>(pal::timer::id::t1, io::resource_id::MOTOR1);
    m_dma = device::claim_device<pal::dma_device>(pal::timer::id::t1, io::resource_id::MOTOR1);

	// Configure dma for transmitting duty cycles to timer pwm
    static constexpr auto tim_channel = static_cast<uint32_t>(pal::timer::channel::ch1);
    m_dma->configure_dma(m_timer, tim_channel);
	m_dma->enable_irq(routine::create<dshot, &dshot::irq_handler>(*this));

	// Configure timer pwm
    m_timer->configure_pwm(0, 917/2, pal::timer::channel::ch1);

	// Start the timer
    m_timer->start_pwm(pal::timer::channel::ch1, m_buffer);
}

void dshot::write(uint16_t value)
{
   // Value should be between 0 and 2047
    if(value > 2047)
    {
         value = 2047;
    }
    
	prepare_dma_buffer(value);
	
    m_timer->start_pwm(pal::timer::channel::ch1, m_buffer);
}

/**
 * The issue here is that we are getting the half transfere complete and the full transfer complete interrupts.
 * That's why, for now we hardcoded this shit
*/
void dshot::irq_handler(size_t channel)
{
	static uint32_t counter = 0;
	if (counter){
		counter = 0;
		m_timer->stop_pwm(pal::timer::channel::ch1);
	}else {
		counter = 1;
	}
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

	for(uint32_t i = 0; i < 16; i++)
	{
		m_motor_dma_buffer[i] = (packet & 0x8000) ? MOTOR_BIT_1 : MOTOR_BIT_0;
		packet <<= 1;
	}

	m_motor_dma_buffer[16] = 0;
}
