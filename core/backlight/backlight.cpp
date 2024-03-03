#include "backlight.h"
#include "color.h"

namespace core::backlight
{

Backlight::Backlight(Device& device, schemes::Scheme** schemes, int num_schemes)
    : device{device}, num_schemes{num_schemes}, schemes{schemes}
{
    for (uint8_t i = 0; i < common::constants::TOTAL_NUM_LEDS; ++i)
    {
        led_states[i].description = &common::constants::LED_PROPERTIES[i];
    }
    schemes[current_scheme_index]->reset();
}

void Backlight::increment_scheme()
{
    current_scheme_index = (current_scheme_index + 1) % num_schemes;
    schemes[current_scheme_index]->reset();
}

void Backlight::update(const core::keyboard::KeyboardScanResult& scan_result)
{
    auto* scheme = schemes[current_scheme_index];
    scheme->update(scan_result, led_states);
    for (uint8_t i = 0; i < common::constants::TOTAL_NUM_LEDS; ++i)
    {
        LEDState& state = led_states[i];
        auto c = state.update(device);
        device.set_led(i, c.get_r_byte(), c.get_g_byte(), c.get_b_byte());

    }
    device.update_leds();
}

void Backlight::signal_failure()
{
    for (uint8_t i = 0; i < common::constants::TOTAL_NUM_LEDS; ++i)
    {
        LEDState& state = led_states[i];
        state.start_fade(device, colors::RED, 10000);
    }
}

}
