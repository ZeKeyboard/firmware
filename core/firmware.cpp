#include "firmware.h"
#include "../common/constants.h"
#include "keyboard/communication.h"

namespace core
{

const int CYCLE_TIME_MICROS = 16000;

Firmware::Firmware(Device& device) : device{device}, key_scanner{device}
{
    // TODO load from SD card when possible
    keymap.load_default();
}

void Firmware::update()
{
    device.start_timer();
    keyboard::KeyboardScanResult result;
    key_scanner.scan(result);
    keymap.translate_keyboard_scan_result(result, key_queue);
    keyboard::communication::send_key_report(key_queue, device);

    // TODO remove this
    for (int i = 0; i < common::constants::TOTAL_NUM_LEDS; ++i)
    {
        device.set_led(i, 255, 0, 0);
    }
    device.update_leds();

    const uint32_t elapsed = device.get_timer_micros();
    if (elapsed < CYCLE_TIME_MICROS)
    {
        device.sleep_micros(CYCLE_TIME_MICROS - elapsed);
    }
}

}
