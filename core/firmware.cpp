#include "firmware.h"

namespace core
{

Firmware::Firmware(Device& device) : device{device}
{ }

void Firmware::init()
{
    device.gpio_setup(13, PinMode::OUT);
}

void Firmware::update()
{
    device.gpio_write(13, true);
    device.sleep_millis(100);
    device.gpio_write(13, false);
    device.sleep_millis(100);
}

}
