
#include "drivers/platform.hpp"
#include "drivers/stm32/common/stm32_uart.hpp"
#include "drivers/pal/uart.hpp"
#include "stm32_uart_impl.hpp"
#include "drivers/common/hardware.hpp"
#include "stm32_uart.hpp"
#include "config.hpp"
#include "drivers/rcc.h"
#include "drivers/pal/global_io.hpp"
#include "drivers/pal/isr.hpp"

#include "etl/array.h"
#include "etl/map.h"
#include "etl/delegate.h"

// Private compile time functions

/* mode table */
static constexpr size_t mode_count = static_cast<size_t>(pal::uart::mode::count);
static const etl::unordered_map<pal::uart::mode, uint32_t, mode_count> mode_table {
    {pal::uart::mode::tx_rx, UART_MODE_TX_RX},
    {pal::uart::mode::tx, UART_MODE_TX},
    {pal::uart::mode::rx, UART_MODE_RX}
};


static etl::map<pal::uart::id, UART_HandleTypeDef*, UARTDEV_COUNT> uart_handle_table = {};


uart_device_stm32::uart_device_stm32(pal::uart::id dev_id)
    : pal::uart_device(dev_id), m_handle()
{
    init_handle();
}

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
    HAL_UART_DeInit(&m_handle);
}

/**
 * Transmit data in blocking mode
*/
pal::uart::status uart_device_stm32::send(const void *buffer, uint32_t size)
{
    HAL_UART_Transmit(&m_handle, static_cast<const uint8_t*>(buffer), size, 1000);
    return pal::uart::status::ok;
}

/*
*/
pal::uart::status uart_device_stm32::send_nonblocking(const void *buffer, uint32_t size, bool recursive)
{
    HAL_UART_Transmit_IT(&m_handle, static_cast<const uint8_t*>(buffer), size);
    return pal::uart::status::ok;
}

pal::uart::status uart_device_stm32::receive(void *buffer, uint32_t size)
{
    HAL_UART_Receive(&m_handle, static_cast<uint8_t*>(buffer), size, 1000);
    return pal::uart::status::ok;
}

pal::uart::status uart_device_stm32::receive_nonblocking(void *buffer, uint32_t size, bool recursive)
{
    HAL_UART_Receive_IT(&m_handle, static_cast<uint8_t*>(buffer), size);
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
    
    // Insert c struct interface into table
    uart_handle_table.insert({m_dev_id, &m_handle});
}

// *****************************************************************************
// Uart isr handlers
// *****************************************************************************

extern "C" {

    void USART1_IRQHandler(void)
    {
        if (uart_handle_table.find(pal::uart::id::u1) != uart_handle_table.end()) {
            // Configured class instance callback
            isr::get_interrupt_vectors_instance().call<isr::vector_id::UART1_IRQ_HANDLER>();
            // HAL library callback
            HAL_UART_IRQHandler(uart_handle_table.at(pal::uart::id::u1));
            return;
        }
        // uart isr callback (for configuration) 
    }

    void USART2_IRQHandler(void)
    {
        if (uart_handle_table.find(pal::uart::id::u2) != uart_handle_table.end()) {
            // Configured class instance callback
            isr::get_interrupt_vectors_instance().call<isr::vector_id::UART2_IRQ_HANDLER>();
            // HAL library callback
            HAL_UART_IRQHandler(uart_handle_table.at(pal::uart::id::u2));
            return;
        }
        // uart isr callback (for configuration) 
    }

    void USART3_IRQHandler(void)
    {
        if (uart_handle_table.find(pal::uart::id::u3) != uart_handle_table.end()) {
            // Configured class instance callback
            isr::get_interrupt_vectors_instance().call<isr::vector_id::UART3_IRQ_HANDLER>();
            // HAL library callback
            HAL_UART_IRQHandler(uart_handle_table.at(pal::uart::id::u3));
            return;
        }
        // uart isr callback (for configuration) 
    }

    void UART4_IRQHandler(void)
    {
        if (uart_handle_table.find(pal::uart::id::u4) != uart_handle_table.end()) {
            // Configured class instance callback
            isr::get_interrupt_vectors_instance().call<isr::vector_id::UART4_IRQ_HANDLER>();
            // HAL library callback
            HAL_UART_IRQHandler(uart_handle_table.at(pal::uart::id::u4));
            // Custom uart driver callback
            return;
        }
        // uart isr callback (for configuration) 
    }

    void UART5_IRQHandler(void)
    {
        if (uart_handle_table.find(pal::uart::id::u5) != uart_handle_table.end()) {
            // Configured class instance callback
            isr::get_interrupt_vectors_instance().call<isr::vector_id::UART5_IRQ_HANDLER>();
            // HAL library callback
            HAL_UART_IRQHandler(uart_handle_table.at(pal::uart::id::u5));
            return;
        }
        // uart isr callback (for configuration) 
    }

    void USART6_IRQHandler(void)
    {
        if (uart_handle_table.find(pal::uart::id::u6) != uart_handle_table.end()) {
            // Configured class instance callback
            isr::get_interrupt_vectors_instance().call<isr::vector_id::UART6_IRQ_HANDLER>();
            // HAL library callback
            HAL_UART_IRQHandler(uart_handle_table.at(pal::uart::id::u6));
            // Custom uart driver callback
            return;
        }
        // uart isr callback (for configuration) 
    }

    void UART7_IRQHandler(void)
    {
        if (uart_handle_table.find(pal::uart::id::u7) != uart_handle_table.end()) {
            // Configured class instance callback
            isr::get_interrupt_vectors_instance().call<isr::vector_id::UART7_IRQ_HANDLER>();
            // HAL library callback
            HAL_UART_IRQHandler(uart_handle_table.at(pal::uart::id::u7));
            return;
        }
        // uart isr callback (for configuration) 
    }

    void UART8_IRQHandler(void)
    {
        if (uart_handle_table.find(pal::uart::id::u8) != uart_handle_table.end()) {
            // Configured class instance callback
            isr::get_interrupt_vectors_instance().call<isr::vector_id::UART8_IRQ_HANDLER>();
            // HAL library callback
            HAL_UART_IRQHandler(uart_handle_table.at(pal::uart::id::u8));
            return;
        }
        // uart isr callback (for configuration) 
    }

    void UART9_IRQHandler(void)
    {
        if (uart_handle_table.find(pal::uart::id::u9) != uart_handle_table.end()) {
            // Configured class instance callback
            isr::get_interrupt_vectors_instance().call<isr::vector_id::UART9_IRQ_HANDLER>();
            // HAL library callback
            HAL_UART_IRQHandler(uart_handle_table.at(pal::uart::id::u9));
            return;
        }
        // uart isr callback (for configuration) 
    }
}
