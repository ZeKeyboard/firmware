#pragma once

#include <stdint.h>
#include <cmath>

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

    /**
     * Creates a color from HSV values, where the hue, saturation and value
     * is in the range [0, 1].
     */
    static Color from_hsv(float hue, float saturation, float value)
    {
        // This function was AI-generated
        const float h = hue * 6.0f;
        const float f = h - floor(h);
        const float p = value * (1.0f - saturation);
        const float q = value * (1.0f - saturation * f);
        const float t = value * (1.0f - saturation * (1.0f - f));

        if (h < 1.0f)
        {
            return Color{value, t, p};
        }
        else if (h < 2.0f)
        {
            return Color{q, value, p};
        }
        else if (h < 3.0f)
        {
            return Color{p, value, t};
        }
        else if (h < 4.0f)
        {
            return Color{p, q, value};
        }
        else if (h < 5.0f)
        {
            return Color{t, p, value};
        }
        else
        {
            return Color{value, p, q};
        }
    }
};

}
