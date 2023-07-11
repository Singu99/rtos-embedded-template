#pragma once

#include "runnable.hpp"
#include "memory/pool_allocator.hpp"
// #include "drivers/platform_abstraction_layer/gpio.h"

class CoreController : public Runnable, public PoolAllocator<CoreController, 1> {
public:
    CoreController();
    ~CoreController() = default;

    // Running thread will execute this function
    virtual void Run() override;
    virtual void Init() override;

private:        // Devices


};