#pragma once

#include "scheme.h"
#include "../../../device.h"
#include <cstdint>

namespace core::backlight::schemes
{

class Lights : public Scheme
{
public:
    Lights(Device& device) : Scheme{device} { }

    void reset() override;

    void update(const core::keyboard::KeyboardScanResult& scan_result,
        core::backlight::LEDState led_states[common::constants::TOTAL_NUM_LEDS]) override;
private:
    uint64_t it;
};

}
