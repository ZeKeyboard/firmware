#pragma once

#include <cmath>
#include <type_traits>
#include <stdint.h>

namespace core::util
{

template<typename T>
T clamp(T value, T min, T max)
{
    static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
    return std::min(std::max(value, min), max);
}

template<typename T>
T wrap_around(T value, T min, T max)
{
    static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
    T result = value;
    T diff = max - min;
    while (result < min || result > max)
    {
        if (result < min)
        {
            result += diff + 1;
        }
        else
        {
            result -= diff + 1;
        }
    }
    return result;
}

constexpr int32_t ceil(float num)
{
    // https://stackoverflow.com/a/31962570
    return (static_cast<float>(static_cast<int32_t>(num)) == num)
        ? static_cast<int32_t>(num)
        : static_cast<int32_t>(num) + ((num > 0) ? 1 : 0);
}


/**
 * Like ceil, but if the input is an integer, it will add 1.
 */
constexpr int32_t always_ceil(float num)
{
    const int32_t ceiled = ceil(num);
    return (static_cast<float>(ceiled) == num)
        ? ceiled + 1
        : ceiled;
}

constexpr bool is_in_bounds(uint8_t height, uint8_t width, float x, float y)
{
    return
        x >= 0.0f &&
        y >= 0.0f &&
        x <= static_cast<float>(width - 1) &&
        y <= static_cast<float>(height - 1);
}

}
