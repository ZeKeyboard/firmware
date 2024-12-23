#include "lights.h"
#include <cmath>


namespace core::backlight::schemes
{

const uint32_t FADE_TIME = 1000;
const float SPEED = 0.1f;
const float LOGO_SPEED = 0.001f;

void Lights::reset()
{
    it = 0;
}


void Lights::update(const core::keyboard::KeyboardScanResult& scan_result,
    core::backlight::LEDState led_states[common::constants::TOTAL_NUM_LEDS])
{
    const float logo_hue = (cos(static_cast<float>(it) * LOGO_SPEED) + 1.0f) / 2.0f;
    const Color logo_color = Color::from_hsv(logo_hue, 1.0f, 1.0f);
    led_states[common::constants::LOGO_LED_INDEX].color = logo_color;
    for (int i = 0; i < scan_result.num_just_pressed; ++i)
    {
        const common::LEDDescription pressed = scan_result.just_pressed[i]->get_associated_led();
        const auto index = pressed.strip_index;
        auto& state = led_states[index];
        const float hue = (cos(static_cast<float>(it) * SPEED) + 1.0f) / 2.0f;
        const Color color = Color::from_hsv(hue, 1.0f, 1.0f);

        state.start_fade(device, color, FADE_TIME);
    }
    it++;
}

}
