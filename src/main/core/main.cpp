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

CoreController* core;
RxController* rx;

int main()
{
    pal::LayerInit();

    System::Init();

    osKernelInitialize();

    // Controller initialization
    core = Factory::create<CoreController>();
    rx = Factory::create<RxController>();

    // TODO: Change to std::optional
    if (core == nullptr || rx == nullptr)   while (1);
    
    core->Init();
    rx->Init();

    osKernelStart();

    while (1);
    
    return 0;
}