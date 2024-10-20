#include "ledstate.h"
#include <cmath>
#include <cstdlib>

namespace core::backlight
{


void LEDState::start_blink(const Device& device, BlinkType blink_type, const uint32_t period)
{
    blinking = true;
    blink_timer.duration = period;
    blink_state = 1.0;
    current_blink_type = blink_type;
    blink_timer.start(device);
}

void LEDState::start_fade(const Device& device, const Color& fade_start_color, const uint32_t fade_time)
{
    fading = true;
    fade_timer.duration = fade_time;
    fade_timer.start(device);
    this->fade_start_color = fade_start_color;
}

void LEDState::reset()
{
    blinking = false;
    fading = false;
    color = colors::BLACK;
}

bool LEDState::is_blinking() const
{
    return blinking;
}

bool LEDState::get_blink_state() const
{
    return blink_state;
}

bool LEDState::is_fading() const
{
    return fading;
}

Color LEDState::update(const Device& device)
{
    if (blinking)
    {
        blink_timer.update(device);
        if (blink_timer.is_finished())
        {
            blink_timer.start(device);
        }
        float blink = (blink_timer.progress() * 2.0) - 1.0; // [-1, 1]
        if (current_blink_type == BlinkType::BINARY)
        {
            blink_state = blink > 0.0 ? 1.0 : 0.0;
        }
        else if (current_blink_type == BlinkType::LINEAR)
        {
            blink_state = std::abs(blink);
        }
        else if (current_blink_type == BlinkType::SINEWAVE)
        {
            blink_state = (std::sin(blink * M_PI) + 1.0) / 2.0;
        }
        return color * blink_state;
    }
    if (fading)
    {
        fade_timer.update(device);
        if (fade_timer.is_finished())
        {
            fading = false;
            return color;
        }
        const auto progress = fade_timer.progress();
        return (fade_start_color * (1.0f - progress)) + (color * progress);
    }
    return color;
}

}
