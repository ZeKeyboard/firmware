#pragma once

#include "../../common/constants.h"
#include "ledstate.h"


namespace core::backlight
{

class ScreenSaver
{
public:
    void init();

    void update();

    void draw(LEDState led_states[common::constants::TOTAL_NUM_LEDS]);

private:
    util::Vector2D position;
    util::Vector2D velocity;

    uint64_t it = 0;
};

}
