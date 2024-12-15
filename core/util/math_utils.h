#pragma once

#include <cmath>
#include <type_traits>

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

}
