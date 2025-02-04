#include "backlight.h"
#include "color.h"
#include "../keyboard/keyutils.h"
#include "ledstate.h"
#include <algorithm>
#include <cmath>
#include <cstdint>


namespace core::backlight
{

constexpr int BRIGHTNESS_STEP = 32;
constexpr uint32_t MILLIS_UNTIL_SCREENSAVER = 1000 * 60 * 5;
constexpr float SCREENSAVER_HUE_SPEED = 0.001f;
constexpr int SCREENSAVER_DIVIDER = 16;


Backlight::Backlight(Device& device, schemes::Scheme** schemes, int num_schemes)
    : device{device}, num_schemes{num_schemes}, schemes{schemes}
{
    for (uint8_t i = 0; i < common::constants::TOTAL_NUM_LEDS; ++i)
    {
        led_states[i].description = &common::constants::LED_PROPERTIES[i];
    }
    schemes[current_scheme_index]->reset();
    screensaver_timer.duration = MILLIS_UNTIL_SCREENSAVER;
    screensaver_timer.start(device);
}

void Backlight::increment_scheme()
{
    current_scheme_index = (current_scheme_index + 1) % num_schemes;
    schemes[current_scheme_index]->reset();

    // reset the RGB led strip
    for (uint8_t i = 0; i < common::constants::TOTAL_NUM_LEDS; ++i)
    {
        LEDState& state = led_states[i];
        state.reset();
    }
}

void Backlight::reset_all_states()
{
    for (uint8_t i = 0; i < common::constants::TOTAL_NUM_LEDS; ++i)
    {
        led_states[i].reset();
    }
}

void Backlight::update(const core::keyboard::KeyboardScanResult& scan_result,
                       const core::keyboard::KeyMap& keymap,
                       uint16_t led_state)
{
    int led_indices_to_highlight[3] = {-1, -1, -1};
    int num_leds_to_highlight = 0;

    if (screensaver_active)
    {
        screensaver_update();

        if (scan_result.are_any_keys_pressed())
        {
            screensaver_active = false;
            screensaver_timer.start(device);
        }
    }
    else
    {
        if (highlight_keys_on_layer && keymap.current_layer != 0)
        {
            if (highlighted_layer != keymap.current_layer)
            {
                reset_all_states();
                highlighted_layer = keymap.current_layer;
                start_blink_on_layer_modifiers(highlighted_layer, keymap);
            }
            highlight_layer_keys(keymap);
        }
        else
        {
            stop_blink_on_layer_modifiers(highlighted_layer, keymap);
            highlighted_layer = 0;
            if (!configure_mode)
            {
                auto scheme = schemes[current_scheme_index];
                scheme->update(scan_result, led_states);
            }
        }
        // view keyboard led state
        if (core::keyboard::util::get_numlock_state(led_state))
        {
            led_indices_to_highlight[num_leds_to_highlight] = find_led_index_of_keycode(0xF053, keymap);
            num_leds_to_highlight++;
        }
        if (core::keyboard::util::get_capslock_state(led_state))
        {
            led_indices_to_highlight[num_leds_to_highlight] = find_led_index_of_keycode(0xF039, keymap);
            num_leds_to_highlight++;
        }
        if (core::keyboard::util::get_scrolllock_state(led_state))
        {
            led_indices_to_highlight[num_leds_to_highlight] = find_led_index_of_keycode(0xF047, keymap);
            num_leds_to_highlight++;
        }

        if (scan_result.are_any_keys_pressed())
        {
            screensaver_timer.start(device);
        }
        screensaver_timer.update(device);
        screensaver_active = screensaver_timer.is_finished();
        if (screensaver_active)
        {
            reset_all_states();
        }
    }

    // set the RGB led strip
    for (uint8_t i = 0; i < common::constants::TOTAL_NUM_LEDS; ++i)
    {
        LEDState& state = led_states[i];
        auto c = state.update(device);
        bool led_override = false;
        for (int j = 0; j < num_leds_to_highlight; ++j)
        {
            if (led_indices_to_highlight[j] == i)
            {
                led_override = true;
                break;
            }
        }
        if (led_override)
        {

            device.set_led(i, 255, 255, 255);
        }
        else
        {
            device.set_led(i, c.get_r_byte(), c.get_g_byte(), c.get_b_byte());
        }
    }

    device.update_leds();
}


void Backlight::screensaver_update()
{
    reset_all_states();
    screensaver_it++;
    const float hue = (cos(static_cast<float>(screensaver_it) * SCREENSAVER_HUE_SPEED) + 1.0f) / 2.0f;
    const Color color = Color::from_hsv(hue, 1.0f, 1.0f);
    int index = static_cast<int>(std::floor(screensaver_it / SCREENSAVER_DIVIDER)) % common::constants::TOTAL_NUM_LEDS;
    led_states[index].color = color;
}


int Backlight::find_led_index_of_keycode(uint16_t keycode, const core::keyboard::KeyMap& keymap)
{
    for (uint8_t i = 0; i < common::constants::TOTAL_NUM_LEDS; ++i)
    {
        LEDState& state = led_states[i];
        const auto& led = state.description;
        if (led->key == nullptr)
        {
            continue;
        }
        // just look on layer 1
        const auto action = keymap.get_action(0, led->key->row, led->key->col);
        if (action != nullptr)
        {
            const auto code = action->sequence[0].key;
            if (code == keycode)
            {
                return i;
            }
        }
    }
    return -1;
}


void Backlight::start_blink_on_layer_modifiers(int layer, const core::keyboard::KeyMap& keymap)
{
    for (uint8_t i = 0; i < common::constants::TOTAL_NUM_LEDS; ++i)
    {
        LEDState& state = led_states[i];
        const auto& led = state.description;
        if (led->key == nullptr)
        {
            continue;
        }
        // layer modifiers are always on layer 0
        const auto action = keymap.get_action(0, led->key->row, led->key->col);
        if (action != nullptr)
        {
            const auto code = action->sequence[0].key;
            if (core::keyboard::util::key_is_layer_toggle_modifier(code)
                && core::keyboard::util::get_layer_toggle_modifier_layer(code) == layer)
            {
                state.start_blink(device);
            }
        }
    }
}


void Backlight::stop_blink_on_layer_modifiers(int layer, const core::keyboard::KeyMap& keymap)
{
    for (uint8_t i = 0; i < common::constants::TOTAL_NUM_LEDS; ++i)
    {
        LEDState& state = led_states[i];
        const auto& led = state.description;
        if (led->key == nullptr)
        {
            continue;
        }
        // layer modifiers are always on layer 0
        const auto action = keymap.get_action(0, led->key->row, led->key->col);
        if (action != nullptr)
        {
            const auto code = action->sequence[0].key;
            if (core::keyboard::util::key_is_layer_toggle_modifier(code)
                && core::keyboard::util::get_layer_toggle_modifier_layer(code) == layer)
            {
                state.reset();
            }
        }
    }
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
                state.color = colors::YELLOW;
            }
        }
        else
        {
            state.color = colors::BLACK;
        }
    }

    // highlight layer modifiers
    for (uint8_t i = 0; i < common::constants::TOTAL_NUM_LEDS; ++i)
    {
        LEDState& state = led_states[i];
        const auto& led = state.description;
        if (led->key == nullptr)
        {
            state.color = colors::BLACK;
            continue;
        }
        const auto action = keymap.get_action(0,
                                              led->key->row,
                                              led->key->col);
        if (action != nullptr)
        {
            const auto code = action->sequence[0].key;
            if (core::keyboard::util::key_is_layer_toggle_modifier(code))
            {
                state.color = colors::GREEN;
            }
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
        state.color = colors::GREEN;
        state.start_blink(device, BlinkType::BINARY, 3000);
    }
}

void Backlight::set_configure_mode(bool configure_mode, const core::keyboard::KeyMap& keymap)
{
    this->configure_mode = configure_mode;

    for (uint8_t i = 0; i < common::constants::TOTAL_NUM_LEDS; ++i)
    {
        LEDState& state = led_states[i];
        state.reset();
    }
    if (configure_mode)
    {
        for (uint8_t i = 0; i < common::constants::TOTAL_NUM_LEDS; ++i)
        {
            LEDState& state = led_states[i];
            state.color = colors::YELLOW;
            state.start_blink(device, BlinkType::SINEWAVE, 2000);

            // look for and highlight the toggle key
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
                const auto code = action->sequence[0].key;
                if (code == common::constants::CONTROL_CONFIG_MODE_TOGGLE)
                {
                    state.reset();
                    state.color = colors::GREEN;
                }
            }
        }
    }
}

void Backlight::increase_brightness()
{
    brightness = std::min(127, brightness + BRIGHTNESS_STEP);
    device.set_backlight_brightness(static_cast<uint8_t>(brightness));
}

void Backlight::decrease_brightness()
{
    brightness = std::max(0, brightness - BRIGHTNESS_STEP);
    device.set_backlight_brightness(static_cast<uint8_t>(brightness));
}

void Backlight::set_current_scheme_index(int index)
{
    current_scheme_index = std::min(num_schemes - 1, index);
    schemes[current_scheme_index]->reset();
}

}
