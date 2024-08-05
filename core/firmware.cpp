#include "firmware.h"
#include "../common/constants.h"
#include "backlight/schemes/wave.h"
#include "keyboard/communication.h"
#include "keyboard/keymap_loader.h"

namespace core
{

const int CYCLE_TIME_MICROS = 16000;

Firmware::Firmware(Device& device) :
    device{device},
    key_scanner{device},

    wave{device},

    backlight{device, schemes, 1}
{ }

void Firmware::update()
{
    mouse_state.reset();
    if (!loaded_keymap)
    {
        const bool success = keyboard::KeyMapLoader::load_from_sd_else_default(device, keymap, settings);
        if (success)
        {
            backlight.signal_success();
        }
        else
        {
            backlight.signal_failure();
        }
        loaded_keymap = true;

        mouse_state.mouse_speed = settings.mouse_speed;
        mouse_state.mouse_acceleration = settings.mouse_acceleration;
    }
    device.start_timer();
    key_scanner.scan(keyboard_scan_result);
    keymap.translate_keyboard_scan_result(keyboard_scan_result, key_queue, mouse_state);
    keyboard::communication::send_key_report(key_queue, device);
    keyboard::communication::send_mouse_commands(mouse_state, device);
    backlight.update(keyboard_scan_result);

    const uint32_t elapsed = device.get_timer_micros();
    if (elapsed < CYCLE_TIME_MICROS)
    {
        device.sleep_micros(CYCLE_TIME_MICROS - elapsed);
    }

    // stty 9600 -F /dev/ttyACM0
    if (device.serial_data_available())
    {
        char* ascii_buffer;
        uint32_t num_read_bytes;
        device.serial_read(ascii_buffer, num_read_bytes);

        const bool success = device.sd_write(
            common::constants::KEYMAP_FILENAME,
            ascii_buffer,
            num_read_bytes);

        delete[] ascii_buffer;
        if (success)
        {
            backlight.signal_success();
        }
        else
        {
            backlight.signal_failure();
        }
    }
}

}
