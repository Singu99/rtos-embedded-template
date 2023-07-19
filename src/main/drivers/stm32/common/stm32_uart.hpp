#pragma once 

#include "drivers/pal/uart.hpp"

#include "drivers/platform.hpp"



class uart_device_stm32 : public pal::uart_device {
public:
    uart_device_stm32(pal::uart::id dev_id);
    ~uart_device_stm32();

protected:

    virtual pal::uart::status open(pal::uart::bus_comm com, pal::uart::mode mode, uint32_t baudrate) override;
    virtual void close() override;
    virtual pal::uart::status send(void* buffer, uint32_t size) override;
    virtual pal::uart::status send_nonblocking(void* buffer, uint32_t size, bool recursive = false) override;
    virtual pal::uart::status receive(void* buffer, uint32_t size) override;
    virtual pal::uart::status receive_nonblocking(void* buffer, uint32_t size, bool recursive = false) override;

private:
    void init_handle();
    void interrupt_handler();
private:
    UART_HandleTypeDef m_handle;
};