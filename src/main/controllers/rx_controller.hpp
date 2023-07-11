#pragma once

#include "runnable.hpp"
#include "memory/pool_allocator.hpp"

class RxController : public Runnable, public PoolAllocator<RxController, 1> {

public:
    RxController();
    ~RxController() = default;

    uint32_t getChannel(uint8_t channel) const { return 0; }

    // Running thread will execute this function
    virtual void Run() override;
    virtual void Init() override;
private:

};