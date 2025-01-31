#pragma once

#include "../../../device.h"
#include "../../keyboard/keyscan.h"
#include "../ledstate.h"
#include "scheme.h"
#include <cstdint>

namespace core::backlight::schemes
{

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
