#pragma once

#include <etl/array.h>
#include <etl/span.h>

#include "rx/rx.hpp"
#include "drivers/pal/timer.hpp"
#include "ghst_protocol.hpp"



#define GHST_MAX_NUM_CHANNELS           16

struct rxConfig_s;
struct rxRuntimeState_s;

class Ghst : public Rx {
public:
    Ghst();
    ~Ghst() = default;

    // called from telemetry/ghst.c
    void ghstRxWriteTelemetryData(const void *const data, const int len);
    void ghstRxSendTelemetryData(void);
    uint8_t ghstRxGetTelemetryBufLen(void);

public:
    // Rx interface
    virtual float ReadRawRc(uint8_t channel) override;
    virtual uint8_t FrameStatus() override;
    virtual bool ProcessFrame() override;
    virtual uint32_t FrameTime() override;

public: 
    // Interrupts
    void OnRxInterrupt(size_t id);


private: 
    void rxSwapFrameBuffers(void);
    uint8_t ghstFrameCRC(const ghstFrame_t *const pGhstFrame);

    
private:
    bool ghstFrameAvailable;
    bool ghstValidatedFrameAvailable;
    bool ghstTransmittingTelemetry;
    etl::array<ghstFrame_t,2> ghstFrameBuffer;

    ghstFrame_t *ghstIncomingFrame;     // incoming frame, raw, not CRC checked, destination address not checked
    ghstFrame_t *ghstValidatedFrame;    // validated frame, CRC is ok, destination address is ok, ready for decode

    uint16_t ghstChannelData[GHST_MAX_NUM_CHANNELS];
    ghstRfProtocol_e ghstRfProtocol;

    uint16_t rssiRaw;

    uint32_t ghstRxFrameStartAtUs = 0;
    uint32_t ghstRxFrameEndAtUs = 0;
private:
    uint8_t m_rxUsartData = 0;
    etl::span<uint8_t> rx_buffer = {&m_rxUsartData, 1};

private:
    pal::timer_device* m_timer;

};