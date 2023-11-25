#include "teensy_device.h"
#include <Arduino.h>

void TeensyDevice::sleep_micros(const int micros)
{
    delayMicroseconds(micros);
}

void TeensyDevice::sleep_millis(const int millis)
{
    delay(millis);
}

void TeensyDevice::gpio_setup(const uint8_t pin, const PinMode mode)
{
    pinMode(pin, static_cast<uint8_t>(mode));
}

void TeensyDevice::gpio_write(const uint8_t pin, const bool value)
{
    digitalWrite(pin, value);
}

