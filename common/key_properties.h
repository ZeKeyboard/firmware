#pragma once

#include <stdint.h>

namespace common
{

struct KeyDescription
{
    uint8_t row;
    uint8_t col;
    float x;
    float y;
    float height;
    float width;
};

}
