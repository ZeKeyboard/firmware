#pragma once

#include <cstdint>
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

}
