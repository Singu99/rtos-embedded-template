#include "runnable.hpp"

extern "C" {
    static void start(void* arg)
    {
        Runnable* runnable = static_cast<Runnable*>(arg);
        runnable->Run();
    }
}

Runnable::Runnable(const char* name, const osThreadAttr_t& attr)
    : m_Name(name),
    m_Attr(attr),
    m_ThreadID(osThreadNew(start, this, &m_Attr))
{}
