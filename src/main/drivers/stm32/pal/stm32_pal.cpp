#include "drivers/pal/pal.hpp"

#include "drivers/platform.hpp"

namespace pal {

    void LayerInit()
    {
        #ifdef USE_HAL_DRIVER
        HAL_Init();
        #endif        






    }

}