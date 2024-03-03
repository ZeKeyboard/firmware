#pragma once

#include "../../device.h"
#include "color.h"
#include "ledstate.h"
#include "../../common/constants.h"
#include "../util/timer.h"
#include "schemes/scheme.h"


namespace core::backlight
{

class Backlight
{
public:
    Backlight(Device& device, schemes::Scheme** schemes, int num_schemes);
    void update(const core::keyboard::KeyboardScanResult& scan_result);
    void increment_scheme();

    void signal_failure();

private:
    Color update_fade(LEDState& state);
    Color update_blink(LEDState& state);

    Device& device;
    LEDState led_states[common::constants::TOTAL_NUM_LEDS];

    int current_scheme_index = 0;

    const int num_schemes;
    schemes::Scheme** schemes;
};

}
