#include "backlight.h"

namespace core::backlight
{

Backlight::Backlight(Device& device) : device{device}
{
    for (uint8_t i = 0; i < common::constants::TOTAL_NUM_LEDS; ++i)
    {
        ledStates[i].description = &common::constants::LED_PROPERTIES[i];
    }
}

}
