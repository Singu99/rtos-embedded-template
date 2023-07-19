#include <etl/array.h>

#include "rx.hpp"
#include "ghst.hpp"

#define RX_MAX_COUNT 2

Rx::Rx()
    : m_data(0) ,
    channelData{nullptr},
    frameData{nullptr},
    lastRcFrameTimeUs(0),
    rssiSource(RSSI_SOURCE_NONE)
{
    /* Claim spcified uart device */
    auto optional = device::claim_device<pal::uart_device>(pal::uart::id::u1, io::resource_id::SERIAL_RX);
    if (optional.has_value())   m_uart = optional.value();
    
    /* Claim spcified timer device */
    auto opt_timer = device::claim_device<pal::timer_device>(pal::timer::id::t2, io::resource_id::SERIAL_RX);
    if (opt_timer.has_value())  m_timer = opt_timer.value();
}