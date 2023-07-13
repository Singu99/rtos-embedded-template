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

core_controller* core;
rx_controller* rx;

int main()
{
    pal::layer_init();

    system::init();

    osKernelInitialize();

    // Controller initialization
    core = factory::create<core_controller>();
    rx = factory::create<rx_controller>();

    // TODO: Change to std::optional
    if (core == nullptr || rx == nullptr)   while (1);
    
    core->Init();
    rx->Init();

    osKernelStart();

    while (1);
    
    return 0;
}