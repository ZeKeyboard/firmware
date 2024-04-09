#include "buffer_utils.h"

namespace core::util
{

char hex_from_ascii_char(char c)
{
    if (c >= '0' && c <= '9')
    {
        return c - '0';
    }
    else if (c >= 'A' && c <= 'F')
    {
        return c - 'A' + 10;
    }
    else
    {
        return 0;
    }
}

void ascii_buffer_to_hex_buffer(const char* ascii_buffer,
                                char*& hex_buffer,
                                int ascii_buffer_size,
                                int& hex_buffer_size)
{
    hex_buffer_size = ascii_buffer_size / 2;
    hex_buffer = new char[hex_buffer_size];
    for (int i = 0; i < ascii_buffer_size; i += 4)
    {
        const char high1 = hex_from_ascii_char(ascii_buffer[i]);
        const char low1 = hex_from_ascii_char(ascii_buffer[i + 1]);
        const char high2 = hex_from_ascii_char(ascii_buffer[i + 2]);
        const char low2 = hex_from_ascii_char(ascii_buffer[i + 3]);
        hex_buffer[i / 2] = (high2 << 4) | low2;
        hex_buffer[i / 2 + 1] = (high1 << 4) | low1;
    }
}

}
