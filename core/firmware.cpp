#include "firmware.h"
#include "../common/constants.h"
#include "backlight/schemes/gameoflife.h"
#include "backlight/schemes/wave.h"
#include "keyboard/communication.h"
#include "keyboard/controlstate.h"
#include "keyboard/keymap_loader.h"
#include "util/buffer_utils.h"
#include <cstdint>

namespace core
{

const int CYCLE_TIME_MICROS = 16000;

Firmware::Firmware(Device& device) :
    device{device},
    key_scanner{device},

    config_button{device},

    wave{device},
    gameOfLife{device},
    backlight{device, schemes, NUM_SCHEMES}
{ }

void Firmware::update()
{
    mouse_state.reset();
    if (!loaded_keymap)
    {
        const bool success = keyboard::KeyMapLoader::load_from_sd_else_default(device, keymap, settings);
        if (!success)
        {
            backlight.signal_failure();
        }
        loaded_keymap = true;

        mouse_state.mouse_speed = settings.mouse_speed;
        mouse_state.mouse_acceleration = settings.mouse_acceleration;

        backlight.highlight_keys_on_layer = settings.highlight_layer_keys;
    }
    device.start_timer();
    keyboard::ControlState control;
    key_scanner.scan(keyboard_scan_result);
    keymap.translate_keyboard_scan_result(keyboard_scan_result, key_queue, mouse_state, control);

    keyboard::communication::send_key_report(key_queue, device);
    keyboard::communication::send_mouse_commands(mouse_state, device);

    config_button.update();
    backlight.update(keyboard_scan_result, keymap, device.get_keyboard_leds());

    const uint32_t elapsed = device.get_timer_micros();

    if (control.toggle_config_mode || config_button.state())
    {
        configure_mode = !configure_mode;
        backlight.set_configure_mode(configure_mode, keymap);
    }

    if (control.next_backlight_mode)
    {
        backlight.increment_scheme();
    }

    if (elapsed < CYCLE_TIME_MICROS)
    {
        device.sleep_micros(CYCLE_TIME_MICROS - elapsed);
    }

    // stty 9600 -F /dev/ttyACM0
    if (configure_mode)
    {
        if (!last_configure_mode)
        {
            // this is to prevent immediate reprogramming of the keyboard if there happens to be data in the serial buffer already.
            device.serial_clear();
        }
        if (device.serial_data_available())
        {
            char* ascii_buffer;
            uint32_t num_read_ascii_chars;
            device.serial_read(ascii_buffer, num_read_ascii_chars);

            char* buffer;
            int num_read_bytes;
            core::util::ascii_buffer_to_hex_buffer(
                ascii_buffer, buffer, num_read_ascii_chars, num_read_bytes);
            bool keymapOk = keyboard::KeyMapLoader::verify_keymap(reinterpret_cast<const uint16_t*>(buffer), num_read_bytes / 2);
            if (keymapOk)
            {
                device.sd_write(
                    common::constants::KEYMAP_FILENAME,
                    ascii_buffer,
                    num_read_ascii_chars);
                device.reboot();
            }
            else
            {
                backlight.signal_failure();
            }
            delete[] ascii_buffer;
            delete[] buffer;
        }
    }
    last_configure_mode = configure_mode;
}

}
