#pragma once

#include "drivers/pal/gpio.hpp"

namespace pal {

    class uart {
    public:
        enum class id { u1 = 0, u2, u3, u4, u5, u6, u7, u8, u9 };

        uart(id device_id);
        ~uart();
    private:
        id device_id;
        


    };

}