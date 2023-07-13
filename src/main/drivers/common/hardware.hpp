#pragma once

#include "drivers/pal/uart.hpp"


template <typename hw>
class hardware {
    public:
    template <typename ID>
    static const hw* get(ID device_id);
    
    /*
    *   Idea is that we provide template specializations for the harware device that we are compiling for.
    *   The template specializations will provide the hardware specific details of the device.
    */

};