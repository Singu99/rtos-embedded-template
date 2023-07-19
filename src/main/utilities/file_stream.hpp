#pragma once

#include <chrono>
#include <cstring>

// @Note: Needs to implement write based on descriptor
class FileStream
{
    public:
    using Radix_t = enum class RadixEnum { Binary=2, Octal=8, Decimal=10, Hexadecimal=16, };

    public:
    FileStream();
    FileStream(size_t fd);

    public:
    FileStream& operator<<(const char* string);

    FileStream& operator<<(unsigned int value);

    FileStream& operator<<(Radix_t radix);
    FileStream& operator<<(std::chrono::milliseconds time);

    size_t Descriptor() { return mFileDescriptor; }

    void Configure();

protected:
    size_t mFileDescriptor;
    Radix_t mRadixSetting;
};
