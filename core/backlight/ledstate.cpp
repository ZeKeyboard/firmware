#include "ledstate.h"

namespace core::backlight
{


void LEDState::start_blink(const Device& device, const uint32_t period)
{
    blinking = true;
    blink_timer.duration = period;
    blink_state = true;
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
            blink_state = !blink_state;
            blink_timer.start(device);
        }
        return blink_state ? color : Color{0, 0, 0};
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
