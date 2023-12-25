#include "firmware.h"
#include "../common/constants.h"

namespace core
{


Firmware::Firmware(Device& device) : device{device}, key_scanner{device}
{
    // TODO load from SD card when possible
    keymap.load_default();
}


void Firmware::update()
{
    keyboard::KeyboardScanResult result;
    key_scanner.scan(result);
    keymap.translate_keyboard_scan_result(result, key_queue);

    // TODO remove
    if (key_queue.size() > 10)
    {
        key_queue.pop();
    }
}

}
