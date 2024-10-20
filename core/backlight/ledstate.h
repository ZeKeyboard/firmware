#pragma once

#include "../../device.h"
#include "color.h"
#include "../../common/constants.h"
#include "../util/timer.h"

namespace core::backlight
{

enum class BlinkType
{
    BINARY,
    LINEAR,
    SINEWAVE
};

struct LEDState
{
    /**
     * The current color of the LED, may be overridden by a blink or fade sequence.
     */
    Color color;

    /**
     * Whether the current LED is blinking.
     */
    bool is_blinking() const;

    /**
     * The state of the blinking, true if illuminated and false if off.
     */
    bool get_blink_state() const;

    /**
     * Whether the current LED is fading.
     */
    bool is_fading() const;

    /**
     * Starts a blink sequence on the LED.
     */
    void start_blink(const Device& device, BlinkType blink_type = BlinkType::BINARY, const uint32_t period = common::constants::DEFAULT_BLINK_PERIOD);

    /**
     * Starts a fade sequence on the LED. Will fade from the fade_start_color
     * to the current color.
     */
    void start_fade(const Device& device, const Color& fade_start_color, const uint32_t fade_time = common::constants::DEFAULT_FADE_TIME);

    void reset();

    const common::LEDDescription* description;

    friend class Backlight;

private:

    /**
     * Updates the LED state, returns the current color of the LED.
     */
    Color update(const Device& device);

    Color fade_start_color;
    bool blinking = false;
    bool fading = false;
    float blink_state = 0.0;
    BlinkType current_blink_type;
    util::Timer blink_timer;
    util::Timer fade_timer;
};

}
