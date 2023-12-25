#pragma once

#include <stdint.h>


namespace core::keyboard::util
{

inline bool key_is_modifier(uint16_t key)
{
    return (key & 0xFF00) == 0xE000;
}

inline bool key_is_media(uint16_t key)
{
    return (key & 0xFF00) == 0xE400;
}

inline bool key_is_standard_key(uint16_t key)
{
    return (key & 0xFF00) == 0xF000;
}

inline bool key_is_system_key(uint16_t key)
{
    return (key & 0xFF00) == 0xE200;
}

}
