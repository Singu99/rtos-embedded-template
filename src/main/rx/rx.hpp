#pragma once

#include "drivers/common/device.hpp"

#include "drivers/pal/uart.hpp"
#include "drivers/pal/timer.hpp"

#define RSSI_MAX_VALUE 1023
#define LINK_QUALITY_MAX_VALUE 1023

typedef enum {
    RX_FRAME_PENDING = 0,
    RX_FRAME_COMPLETE = (1 << 0),
    RX_FRAME_FAILSAFE = (1 << 1),
    RX_FRAME_PROCESSING_REQUIRED = (1 << 2),
    RX_FRAME_DROPPED = (1 << 3)
} rxFrameState_e;

typedef enum {
    SERIALRX_NONE = 0,
    SERIALRX_SPEKTRUM2048 = 1,
    SERIALRX_SBUS = 2,
    SERIALRX_SUMD = 3,
    SERIALRX_SUMH = 4,
    SERIALRX_XBUS_MODE_B = 5,
    SERIALRX_XBUS_MODE_B_RJ01 = 6,
    SERIALRX_IBUS = 7,
    SERIALRX_JETIEXBUS = 8,
    SERIALRX_CRSF = 9,
    SERIALRX_SRXL = 10,
    SERIALRX_TARGET_CUSTOM = 11,
    SERIALRX_FPORT = 12,
    SERIALRX_SRXL2 = 13,
    SERIALRX_GHST = 14,
    SERIALRX_SPEKTRUM1024 = 15
} SerialRXType;

typedef enum {
    RSSI_SOURCE_NONE = 0,
    RSSI_SOURCE_ADC,
    RSSI_SOURCE_RX_CHANNEL,
    RSSI_SOURCE_RX_PROTOCOL,
    RSSI_SOURCE_MSP,
    RSSI_SOURCE_FRAME_ERRORS,
    RSSI_SOURCE_RX_PROTOCOL_CRSF,
} rssiSource_e;

class Rx {
public:
    Rx();
    ~Rx() = default;

    enum class RxType : uint8_t {
        GHST, CRSF, SBUS, IBUS, SUMD, PPM, DSM, MAX
    };

    /* Rx interface */
    virtual float ReadRawRc(uint8_t channel) { return 0.0;};
    virtual uint8_t FrameStatus() { return 0; };
    virtual bool ProcessFrame() { return false; };
    virtual uint32_t FrameTime() { return 0;};

protected:
    // Attribs
    uint16_t m_data;

    // rxProvider_t rxProvider;
    // SerialRXType serialrxProvider;
    uint16_t *channelData;
    void *frameData;
    uint32_t lastRcFrameTimeUs;

    rssiSource_e rssiSource;

protected:    // Peripherials
    pal::uart_device* m_uart;
    pal::timer_device* m_timer;

};