#pragma once

#include <optional>
#include "drivers/pal/uart.hpp"

template <typename hw>
class hardware {
    public:
    
    // TODO: Remove optional and make it constexpr. 

    /**
     * The idea is that we provide template specializations for the harware device that we are compiling for.
     * The template specializations will provide the hardware specific details of the device.
     * 
     * @note If it does not return a correct pointer it should not compile.
     */ 
    template <typename ID>
    static const hw* get(ID device_id);
    
};