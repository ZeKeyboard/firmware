#include <Arduino.h>
#include "core/firmware.h"
#include "teensy_device.h"

TeensyDevice device;
core::Firmware firmware{device};

void setup()
{
    firmware.init();
}

void loop()
{
    firmware.update();
}
