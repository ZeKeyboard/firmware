#include "wave.h"
#include <cmath>


namespace core::backlight::schemes
{

void Wave::reset()
{
    it = 0;
}


void Wave::update(const core::keyboard::KeyboardScanResult& scan_result,
    core::backlight::LEDState led_states[common::constants::TOTAL_NUM_LEDS])
{
    const float fade_x = sin(it * SPEED * X_SPEED);
    const float fade_y = sin(it * SPEED * Y_SPEED);
    for (int i = 0; i < common::constants::TOTAL_NUM_LEDS; ++i)
    {
        auto& state = led_states[i];
        const auto x = state.description->x;
        const auto y = state.description->y;

        const float hue = (cos((it * SPEED + x * fade_x + y * fade_y) * MAX_PHASE_DIFFERENCE) + 1.0f) / 2.0f;
        const Color color = Color::from_hsv(hue, 1.0f, 1.0f);
        state.color = color;
    }

    for (int i = 0; i < scan_result.num_pressed; ++i)
    {
        const common::LEDDescription pressed = scan_result.just_pressed[i]->get_associated_led();
        const auto index = pressed.strip_index;
        auto& state = led_states[index];
        state.start_fade(device, colors::WHITE, PRESS_FADE_TIME);
    }

    it++;
}

}
