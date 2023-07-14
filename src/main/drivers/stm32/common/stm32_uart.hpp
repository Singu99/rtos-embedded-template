#pragma once 

#include "drivers/pal/uart.hpp"

#include "drivers/platform.hpp"

class uart_device_stm32 : public pal::uart_device {
public:
    uart_device_stm32(pal::uart::id dev_id);
    ~uart_device_stm32();

    void open(pal::uart::bus bus, pal::uart::mode mode, uint32_t baudrate, pal::uart_interruptable* rsi = nullptr) override;
    void close() override;

protected:
    virtual pal::uart::status send(void* buffer, uint32_t size) override;
    virtual pal::uart::status send_nonblocking(void* buffer, uint32_t size, bool recursive = false) override;
    virtual pal::uart::status receive(void* buffer, uint32_t size) override;
    virtual pal::uart::status receive_nonblocking(void* buffer, uint32_t size, bool recursive = false) override;

};