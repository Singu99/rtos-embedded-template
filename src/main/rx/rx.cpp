#include <array>

#include "rx.hpp"

#include "ghst.hpp"

#define RX_MAX_COUNT 2

Rx::Rx()
    : m_data(0) ,
    channelData{nullptr},
    frameData{nullptr},
    lastRcFrameTimeUs(0),
    rssiSource(RSSI_SOURCE_NONE),
    m_usart(Pal::Usart::Id::ID2)

{
    
}

void Rx::OnRxInterrupt()
{
    
}

void Rx::OnTxInterrupt()
{

}
