#pragma once

#include "runnable.hpp"
#include "memory/pool_allocator.hpp"

#include "rx/ghst.hpp"

class rx_controller : public Runnable, public PoolAllocator<rx_controller,1> {

public:
    rx_controller();
    ~rx_controller() = default;

    float getChannel(uint8_t channel) const { return output; }

    // Running thread will execute this function
    virtual void Run() override;
    virtual void Init() override;
private:
    Ghst m_ghst;
    float output = 0;
};