#include <Arduino.h>
#include "core/firmware.h"
#include "teensy_device.h"

TeensyDevice device;
core::Firmware firmware{device};

void setup()
{
    device.serial_begin(9600);
    firmware.init();
}

void loop()
{
    device.sleep_millis(1000);
    firmware.update();
    const auto leds = device.get_keyboard_leds();
    device.serial_print("leds: ");
    device.serial_println(leds);
}
