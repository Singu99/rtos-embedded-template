#include "main.h"
// #include "mcu.h"

// TODO: Move it to common header. Add precompiled headers
// Remove useless cast warnings
#include "rtos.hpp"

#include "memory/factory.hpp"

#include "drivers/stm32/system.hpp"
#include "drivers/pal/pal.hpp"

#include "controllers/core_controller.hpp"
#include "controllers/rx_controller.hpp"
#include "controllers/dshot_controller.hpp"

namespace mcu
{
    core_controller* core;
    rx_controller* rx;
    dshot_controller* dshot;
}

int main()
{
    pal::layer_init();

    system::init();

    osKernelInitialize();

    // Controller construction
    mcu::core = factory::create<core_controller>();
    mcu::rx = factory::create<rx_controller>();
    mcu::dshot = factory::create<dshot_controller>();
    
    // Controller initialization
    mcu::core->Init();
    mcu::rx->Init();
    mcu::dshot->Init();

    // Start the kernel
    osKernelStart();

    // Should never reach this point
    while (1);
    
    return 0;
}