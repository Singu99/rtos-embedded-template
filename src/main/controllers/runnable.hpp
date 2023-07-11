#pragma once

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wuseless-cast"
#include <cmsis_os.h>
#pragma GCC diagnostic pop

class Runnable {
public:
    Runnable(const char* name, const osThreadAttr_t& attr);

    virtual void Init() {};
    virtual void Run() = 0;

protected:
    const char* m_Name;
    osThreadId_t m_ThreadID;
    const osThreadAttr_t m_Attr;
protected:
    static inline osThreadAttr_t initThreadAttr(const char* name, uint32_t stackSize, osPriority_t priority)
    {
        // Specify the attributes of the thread
        return osThreadAttr_t{
            .name = name,
            .attr_bits = 0,
            .cb_mem = nullptr,
            .cb_size = 0,
            .stack_mem = nullptr,
            .stack_size = stackSize,
            .priority = priority,
            .tz_module = 0,
            .reserved = 0
        };
    }
};