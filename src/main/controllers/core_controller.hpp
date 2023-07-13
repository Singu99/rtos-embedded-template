#pragma once

#include "runnable.hpp"
#include "memory/pool_allocator.hpp"
// #include "drivers/platform_abstraction_layer/gpio.h"

class core_controller : public Runnable, public PoolAllocator<core_controller, 1> {
public:
    core_controller();
    ~core_controller() = default;

    // Running thread will execute this function
    virtual void Run() override;
    virtual void Init() override;

private:        // Devices


};