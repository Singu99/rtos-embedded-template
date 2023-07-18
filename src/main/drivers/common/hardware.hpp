#pragma once

#include <optional>
#include "drivers/pal/uart.hpp"


template <typename hw>
class hardware {
    public:
    template <typename ID>
    static std::optional<const hw*> get(ID device_id) {
        // Unimplemented. I would like to throw a compile time error here.
        return {};
    }
    
    /*
    *   Idea is that we provide template specializations for the harware device that we are compiling for.
    *   The template specializations will provide the hardware specific details of the device.
    */

};