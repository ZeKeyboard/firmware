#pragma once

#include <stdint.h>

namespace core::backlight
{

struct Color
{
    float r = 0;
    float g = 0;
    float b = 0;

    uint8_t get_r_byte() const
    {
        return static_cast<uint8_t>(r * 255.0f);
    }

    uint8_t get_g_byte() const
    {
        return static_cast<uint8_t>(g * 255.0f);
    }

    uint8_t get_b_byte() const
    {
        return static_cast<uint8_t>(b * 255.0f);
    }

    Color operator*(const float f) const
    {
        return Color{
            static_cast<float>(r * f),
            static_cast<float>(g * f),
            static_cast<float>(b * f)};
    }

    Color operator+(const Color& other) const
    {
        return Color{
            static_cast<float>(r + other.r),
            static_cast<float>(g + other.g),
            static_cast<float>(b + other.b)};
    }
};

}
