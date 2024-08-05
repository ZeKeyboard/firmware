#include "backlight.h"
#include "color.h"
#include "../keyboard/keyutils.h"


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

void Backlight::reset_all_states()
{
    for (uint8_t i = 0; i < common::constants::TOTAL_NUM_LEDS; ++i)
    {
        led_states[i].reset();
    }
}

void Backlight::update(const core::keyboard::KeyboardScanResult& scan_result,
                       const core::keyboard::KeyMap& keymap)
{
    if (highlight_keys_on_layer && keymap.current_layer != 0)
    {
        reset_all_states();
        highlight_layer_keys(keymap);
    }
    else
    {
        auto* scheme = schemes[current_scheme_index];
        scheme->update(scan_result, led_states);
    }
    for (uint8_t i = 0; i < common::constants::TOTAL_NUM_LEDS; ++i)
    {
        LEDState& state = led_states[i];
        auto c = state.update(device);
        device.set_led(i, c.get_r_byte(), c.get_g_byte(), c.get_b_byte());
    }
    device.update_leds();
}

void Backlight::highlight_layer_keys(const core::keyboard::KeyMap& keymap)
{
    for (uint8_t i = 0; i < common::constants::TOTAL_NUM_LEDS; ++i)
    {
        LEDState& state = led_states[i];
        const auto& led = state.description;
        if (led->key == nullptr)
        {
            state.color = colors::BLACK;
            continue;
        }
        const auto action = keymap.get_action(keymap.current_layer,
                                              led->key->row,
                                              led->key->col);
        if (action != nullptr)
        {
            // TODO might need more work
            const auto code = action->sequence[0].key;
            if (core::keyboard::util::key_is_valid_standard_key(code))
            {
                state.color = colors::WHITE;
            }
            else if (core::keyboard::util::key_is_mouse_key(code))
            {
                state.color = colors::RED;
            }
            else
            {
                state.color = colors::GREEN;
            }
        }
        else
        {
            state.color = colors::BLACK;
        }
    }
}

void Backlight::signal_failure()
{
    for (uint8_t i = 0; i < common::constants::TOTAL_NUM_LEDS; ++i)
    {
        LEDState& state = led_states[i];
        state.start_fade(device, colors::RED, 10000);
    }
}

void Backlight::signal_success()
{
    for (uint8_t i = 0; i < common::constants::TOTAL_NUM_LEDS; ++i)
    {
        LEDState& state = led_states[i];
        state.start_fade(device, colors::GREEN, 10000);
    }
}

}
