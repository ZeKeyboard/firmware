#pragma once

#include "../../device.h"
#include "color.h"
#include "ledstate.h"
#include "../../common/constants.h"
#include "../util/timer.h"
#include "schemes/scheme.h"
#include "../keyboard/keymap.h"
#include <cstdint>


namespace core::backlight
{
class Backlight
{
public:
    Backlight(Device& device, schemes::Scheme** schemes, int num_schemes);
    void update(const core::keyboard::KeyboardScanResult& scan_result,
                const core::keyboard::KeyMap& keymap,
                uint16_t led_state);
    void increment_scheme();

    void signal_failure();
    void signal_success();

    void increase_brightness();
    void decrease_brightness();

    void set_current_scheme_index(int index);

    bool highlight_keys_on_layer = false;

    void set_configure_mode(bool configure_mode, const core::keyboard::KeyMap& keymap);

private:
    Color update_fade(LEDState& state);
    Color update_blink(LEDState& state);

    void reset_all_states();

    void highlight_key(uint16_t keycode, const core::keyboard::KeyMap& keymap);

    void highlight_layer_keys(const core::keyboard::KeyMap& keymap);

    void start_blink_on_layer_modifiers(int layer, const core::keyboard::KeyMap& keymap);
    void stop_blink_on_layer_modifiers(int layer, const core::keyboard::KeyMap& keymap);

    Device& device;
    LEDState led_states[common::constants::TOTAL_NUM_LEDS];

    int current_scheme_index = 0;

    int highlighted_layer = 0;

    int brightness = 127;

    const int num_schemes;
    schemes::Scheme** schemes;
    bool configure_mode = false;
};

}
