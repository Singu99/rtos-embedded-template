#include "drivers/pal/pal.hpp"

#include "drivers/platform.hpp"

namespace pal {

    void layer_init()
    {
        #ifdef USE_HAL_DRIVER
        HAL_Init();
        #endif        






    }

}