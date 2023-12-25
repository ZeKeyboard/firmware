#include "teensy_device.h"
#include <Arduino.h>
#include <usb_keyboard.h>


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

void TeensyDevice::gpio_write(const uint8_t pin, const PinState value)
{
    digitalWrite(pin, static_cast<uint8_t>(value));
}

PinState TeensyDevice::gpio_read(const uint8_t pin)
{
    return static_cast<PinState>(digitalRead(pin));
}

uint16_t TeensyDevice::get_keyboard_leds()
{
    // declared in usb_keyboard.h
    return keyboard_leds;
}

void TeensyDevice::serial_begin(const uint32_t baud)
{
    Serial.begin(baud);
}

void TeensyDevice::serial_print(const char* str)
{
    Serial.print(str);
}

void TeensyDevice::serial_print(uint8_t val)
{
    Serial.print(val);
}

void TeensyDevice::serial_print(uint16_t val)
{
    Serial.print(val);
}

void TeensyDevice::serial_print(uint32_t val)
{
    Serial.print(val);
}

void TeensyDevice::serial_print(int8_t val)
{
    Serial.print(val);
}

void TeensyDevice::serial_print(int16_t val)
{
    Serial.print(val);
}

void TeensyDevice::serial_print(int32_t val)
{
    Serial.print(val);
}

void TeensyDevice::serial_println(const char* str)
{
    Serial.println(str);
}

void TeensyDevice::serial_println(uint8_t val)
{
    Serial.println(val);
}

void TeensyDevice::serial_println(uint16_t val)
{
    Serial.println(val);
}

void TeensyDevice::serial_println(uint32_t val)
{
    Serial.println(val);
}

void TeensyDevice::serial_println(int8_t val)
{
    Serial.println(val);
}

void TeensyDevice::serial_println(int16_t val)
{
    Serial.println(val);
}

void TeensyDevice::serial_println(int32_t val)
{
    Serial.println(val);
}

void TeensyDevice::set_keyboard_key1(const uint8_t code)
{
    Keyboard.set_key1(code);
}

void TeensyDevice::set_keyboard_key2(const uint8_t code)
{
    Keyboard.set_key2(code);
}

void TeensyDevice::set_keyboard_key3(const uint8_t code)
{
    Keyboard.set_key3(code);
}

void TeensyDevice::set_keyboard_key4(const uint8_t code)
{
    Keyboard.set_key4(code);
}

void TeensyDevice::set_keyboard_key5(const uint8_t code)
{
    Keyboard.set_key5(code);
}

void TeensyDevice::set_keyboard_key6(const uint8_t code)
{
    Keyboard.set_key6(code);
}

void TeensyDevice::set_keyboard_modifier(const uint16_t modifier)
{
    Keyboard.set_modifier(modifier);
}

void TeensyDevice::set_keyboard_media(const uint16_t media)
{
    Keyboard.set_media(media);
}

void TeensyDevice::keyboard_send()
{
    Keyboard.send_now();
}
