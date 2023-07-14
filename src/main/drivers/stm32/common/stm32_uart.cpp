
#include "drivers/stm32/common/stm32_uart.hpp"
#include "drivers/pal/uart.hpp"
#include "stm32_uart_impl.hpp"
#include "drivers/common/hardware.hpp"
#include "stm32_uart.hpp"

uart_device_stm32::uart_device_stm32(pal::uart::id dev_id)
    : pal::uart_device(dev_id)
{

}

void uart_device_stm32::open(pal::uart::bus bus, pal::uart::mode mode, uint32_t baudrate, pal::uart_interruptable *rsi)
{


}

void uart_device_stm32::close()
{


}


pal::uart::status uart_device_stm32::send(void *buffer, uint32_t size)
{
    return pal::uart::status::ok;
}

pal::uart::status uart_device_stm32::send_nonblocking(void *buffer, uint32_t size, bool recursive)
{
    return pal::uart::status::ok;
}

pal::uart::status uart_device_stm32::receive(void *buffer, uint32_t size)
{
    return pal::uart::status::ok;
}

pal::uart::status uart_device_stm32::receive_nonblocking(void *buffer, uint32_t size, bool recursive)
{
    return pal::uart::status::ok;
}
