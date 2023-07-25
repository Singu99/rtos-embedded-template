#pragma once

#include "runnable.hpp"
#include "memory/pool_allocator.hpp"




class dshot_controller : public Runnable, public PoolAllocator<dshot_controller,1> {

public:
    dshot_controller();
    ~dshot_controller() = default;

    // Running thread will execute this function
    virtual void Run() override;
    virtual void Init() override;

private:


};



