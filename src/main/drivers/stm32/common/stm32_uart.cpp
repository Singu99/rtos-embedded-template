
#include "drivers/platform.hpp"
#include "drivers/stm32/common/stm32_uart.hpp"
#include "drivers/pal/uart.hpp"
#include "stm32_uart_impl.hpp"
#include "drivers/common/hardware.hpp"
#include "stm32_uart.hpp"
#include "config.hpp"
#include "drivers/rcc.h"
#include "drivers/pal/global_io.hpp"

#include "etl/array.h"

// Private compile time functions
static constexpr size_t mode_count = static_cast<size_t>(pal::uart::mode::count);

/* mode table */
static const etl::unordered_map<pal::uart::mode, uint32_t, mode_count> mode_table {
    {pal::uart::mode::tx_rx, UART_MODE_TX_RX},
    {pal::uart::mode::tx, UART_MODE_TX},
    {pal::uart::mode::rx, UART_MODE_RX}
};

uart_device_stm32::uart_device_stm32(pal::uart::id dev_id)
    : pal::uart_device(dev_id), m_handle()
{
    init_handle();
}

// TODO: Add more function calls like old driver
pal::uart::status uart_device_stm32::open(pal::uart::bus_comm com, pal::uart::mode mode, uint32_t baudrate)
{
    // Retreive hardware
    const auto uartHardware = hardware<pal::stm32::uart_hardware_t>::get(m_dev_id);
        
    // Init uart structure
    m_handle.Init.BaudRate = baudrate;
    m_handle.Init.Mode = mode_table.at(mode);

    switch (com)
    {
    case pal::uart::bus_comm::full_duplex:
        pal::global_io::configure_pin(m_dev_id, config::rx::get_uart_rx_io(m_dev_id));
        pal::global_io::configure_pin(m_dev_id, config::rx::get_uart_tx_io(m_dev_id));
        HAL_UART_Init(&m_handle);
        break;
    case pal::uart::bus_comm::half_duplex:
        pal::global_io::configure_pin(m_dev_id, config::rx::get_uart_tx_io(m_dev_id));
        HAL_HalfDuplex_Init(&m_handle);
        break;
    default:
        return pal::uart::status::not_supported;
        break;
    }

    HAL_NVIC_SetPriority(uartHardware->rxIrq, 0, 0);
    HAL_NVIC_EnableIRQ(uartHardware->rxIrq);
    return pal::uart::status::ok;
}

void uart_device_stm32::close()
{
    // Hal deinit uart
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

void uart_device_stm32::init_handle()
{
    const auto uartHardware = hardware<pal::stm32::uart_hardware_t>::get(m_dev_id);

    m_handle.Instance = uartHardware->reg;
    m_handle.Init.BaudRate = 0;
    m_handle.Init.WordLength = UART_WORDLENGTH_8B;
    m_handle.Init.StopBits = UART_STOPBITS_1;
    m_handle.Init.Parity = UART_PARITY_NONE;
    m_handle.Init.Mode = UART_MODE_TX_RX;       // Default for now
    
}
