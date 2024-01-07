#pragma once

#include <stdint.h>

namespace common
{

struct KeyDescription;
struct LEDDescription;

struct KeyDescription
{
    uint8_t row;
    uint8_t col;
    float x;
    float y;
    float height;
    float width;
    uint16_t default_key;
    int led_strip_index;

    const LEDDescription& get_associated_led() const;
};


struct LEDDescription
{
    int strip_index;
    float x;
    float y;
    const KeyDescription* key = nullptr;
};

}
