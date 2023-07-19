#include <etl/array.h>
#include <etl/delegate.h>
#include <etl/span.h>

#include "file_stream.hpp"
#include "drivers/pal/uart.hpp"
#include "drivers/common/device.hpp"


// Descripors
static pal::uart_device* uart1 = nullptr;

FileStream::FileStream() 
    : mFileDescriptor(1), mRadixSetting(RadixEnum::Hexadecimal) 
{
}

FileStream::FileStream(size_t fd)
: mFileDescriptor(fd), mRadixSetting(RadixEnum::Hexadecimal) 
{

}

FileStream&  FileStream::operator<<(const char* string)
{
    const size_t length = std::strlen(string);
    etl::span buffer = etl::span(string, length);
    uart1->send(buffer);
    return *this;
}

FileStream &FileStream::operator<<(unsigned int value)
{
    const char* const digits = "0123456789ABCDEF";
    const unsigned int radix = static_cast<unsigned int>(mRadixSetting);
    static constexpr size_t MaxFieldWidth = 34;
    char fielddata[MaxFieldWidth];
    size_t fieldindex = 0;

    int first = 0;
    switch (mRadixSetting)
    {
    case RadixEnum::Binary:
        fielddata[0] = '0';
        fielddata[1] = 'b';
        fieldindex += 2;
        first += 2;
        break;
    case RadixEnum::Octal:
        fielddata[0] = '0';
        fielddata[1] = 'o';
        fieldindex += 2;
        first += 2;
        break;
    case RadixEnum::Decimal:
        break;
    case RadixEnum::Hexadecimal:
        fielddata[0] = '0';
        fielddata[1] = 'x';
        fieldindex += 2;
        first += 2;
        break;
    }

    // calculate digits (they will be reversed)
    unsigned int remainder;
    do {
        remainder = value % radix;
        fielddata[fieldindex] = digits[remainder];
        value /= radix;
        fieldindex += 1;
    } while ( value != 0 );

    // reverse order
    int last = fieldindex-1;
    while ( (last-first) > 0 )
    {
        char tmp = fielddata[last];
        fielddata[last] = fielddata[first];
        fielddata[first] = tmp;
        first += 1;
        last -= 1;
    }

    etl::span<char> buffer(fielddata, fieldindex);
    uart1->send(buffer);
    return *this;
}

FileStream &FileStream::operator<<(Radix_t radix)
{
    mRadixSetting = radix;

    return *this;
}

FileStream &FileStream::operator<<(std::chrono::milliseconds time)
{
    operator<<(time.count());
    operator<<("ms");

    return *this;
}

void FileStream::Configure()
{
    switch (mFileDescriptor)
    {
    case 1:
        auto optional = device::claim_device<pal::uart_device>(pal::uart::id::u1, io::resource_id::FILE_STREAM);
        if (optional.has_value())
        {
            uart1 = optional.value();
            uart1->open(pal::uart::bus_comm::full_duplex, pal::uart::mode::tx, 115200, [](size_t){});
        }
        break;
    }
}
