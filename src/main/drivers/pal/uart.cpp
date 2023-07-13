#include "uart.hpp"



namespace pal {

    uart::uart(uart::id device_id)
        : device_id(device_id)
    {

    }

    uart::~uart() {
    }

}   // namespace pal

