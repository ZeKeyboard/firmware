#include "firmware.h"
#include "../common/constants.h"

namespace core
{

Firmware::Firmware(Device& device) : device{device}, key_scanner{device}
{
    device.gpio_setup(13, PinMode::OUT);
    device.serial_begin(9600);
}


void Firmware::update()
{
    keyboard::KeyboardScanResult result;
    key_scanner.scan(result);
}

}
