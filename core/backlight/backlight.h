#pragma once

#include <stdint.h>
#include "../../device.h"
#include "../../common/key_properties.h"
#include "../../common/constants.h"
#include "color.h"
#include "../util/timer.h"


namespace core::backlight
{

struct LEDState
{
    Color color;

    bool blinking = false;
    util::Timer blink_timer;

    bool fading = false;
    util::Timer fade_timer;

    const common::LEDDescription* description;
};

class Backlight
{
public:
    Backlight(Device& device);
    void update();
private:
    Device& device;
    LEDState ledStates[common::constants::TOTAL_NUM_LEDS];
};

}
