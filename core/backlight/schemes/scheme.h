#pragma once

#include "../../../device.h"
#include "../../keyboard/keyscan.h"
#include "../ledstate.h"

namespace core::backlight::schemes
{

/**
 * Base class for backlight schemes.
 */
class Scheme
{
public:
    Scheme(Device& device) : device{device} { }

    virtual void reset() = 0;

    virtual void update(const core::keyboard::KeyboardScanResult& scan_result,
        core::backlight::LEDState led_states[common::constants::TOTAL_NUM_LEDS]) = 0;

protected:
    Device& device;
};

}
