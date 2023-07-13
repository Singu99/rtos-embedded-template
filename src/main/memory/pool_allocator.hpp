#pragma once

#include "rtos.hpp"

#include <cstdint>

class factory;


template<typename T, size_t MaxElements>
class PoolAllocator {
    friend class factory;
private:
    /**
     * Allocate using CMSIS RTOS memory pool
     * */ 
    static T* allocate()
    {
        osMemoryPoolId_t memory = Memory::getInstance().getPool();
        return static_cast<T*>(osMemoryPoolAlloc(memory, 0));
    }

    static void deallocate(T* object)
    {
        osMemoryPoolId_t memory = Memory::getInstance().getPool();
        osMemoryPoolFree(memory, object);
    }

    class Memory
    {
    public:
        static Memory& getInstance()
        {
            static Memory instance;
            return instance;
        }

        Memory(const Memory&) = delete;
        Memory& operator=(const Memory&) = delete;

        osMemoryPoolId_t getPool() const
        {
            return pool;
        }
    private:
        osMemoryPoolId_t pool;
    private:
        Memory() 
            : pool(osMemoryPoolNew(MaxElements, sizeof(T), NULL))
        {}
        ~Memory() {
            osMemoryPoolDelete(pool);
        }
    };
    
protected:
    PoolAllocator() = default;
    ~PoolAllocator() = default;

private:
    osMemoryPoolId_t pool;
};