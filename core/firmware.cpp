#include "firmware.h"
#include "../common/constants.h"
#include "backlight/schemes/wave.h"
#include "keyboard/communication.h"

namespace core
{

const int CYCLE_TIME_MICROS = 16000;

Firmware::Firmware(Device& device) :
    device{device},
    key_scanner{device},

    wave{device},

    backlight{device, schemes, 1}
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
    backlight.update(result);

    const uint32_t elapsed = device.get_timer_micros();
    if (elapsed < CYCLE_TIME_MICROS)
    {
        device.sleep_micros(CYCLE_TIME_MICROS - elapsed);
    }
}

}
