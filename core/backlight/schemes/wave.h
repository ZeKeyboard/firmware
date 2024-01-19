#pragma once

#include "../../../device.h"
#include "../../keyboard/keyscan.h"
#include "../ledstate.h"
#include "scheme.h"

namespace core::backlight::schemes
{

const float SPEED = 0.00005f;
const float X_SPEED = 0.8f;
const float Y_SPEED = 1.1f;
const float MAX_PHASE_DIFFERENCE = 0.3f;
const uint32_t PRESS_FADE_TIME = 2000;


class Wave : public Scheme
{
public:
    Wave(Device& device) : Scheme{device} { }

    void reset() override;

    void update(const core::keyboard::KeyboardScanResult& scan_result,
        core::backlight::LEDState led_states[common::constants::TOTAL_NUM_LEDS]) override;
private:
    uint64_t it = 0;
};

}
