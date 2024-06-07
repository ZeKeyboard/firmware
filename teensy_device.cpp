#include "teensy_device.h"
#include "generated/hardware_layout.h"
#include <Arduino.h>
#include <usb_keyboard.h>
#include <utility>
#include <SD.h>


TeensyDevice::TeensyDevice(CRGB* leds) : leds{leds}
{ }


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
    Serial.flush();
}

void TeensyDevice::serial_print(uint8_t val)
{
    Serial.print(val);
    Serial.flush();
}

void TeensyDevice::serial_print(uint16_t val)
{
    Serial.print(val);
    Serial.flush();
}

void TeensyDevice::serial_print(uint32_t val)
{
    Serial.print(val);
    Serial.flush();
}

void TeensyDevice::serial_print(int8_t val)
{
    Serial.print(val);
    Serial.flush();
}

void TeensyDevice::serial_print(int16_t val)
{
    Serial.print(val);
    Serial.flush();
}

void TeensyDevice::serial_print(int32_t val)
{
    Serial.print(val);
    Serial.flush();
}

void TeensyDevice::serial_println(const char* str)
{
    Serial.println(str);
    Serial.flush();
}

void TeensyDevice::serial_println(uint8_t val)
{
    Serial.println(val);
    Serial.flush();
}

void TeensyDevice::serial_println(uint16_t val)
{
    Serial.println(val);
    Serial.flush();
}

void TeensyDevice::serial_println(uint32_t val)
{
    Serial.println(val);
    Serial.flush();
}

void TeensyDevice::serial_println(int8_t val)
{
    Serial.println(val);
    Serial.flush();
}

void TeensyDevice::serial_println(int16_t val)
{
    Serial.println(val);
    Serial.flush();
}

void TeensyDevice::serial_println(int32_t val)
{
    Serial.println(val);
    Serial.flush();
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

bool TeensyDevice::serial_data_available()
{
    return Serial.available() > 0;
}

void TeensyDevice::serial_read(char*& buffer, uint32_t& num_read_bytes)
{
    num_read_bytes = Serial.available();
    buffer = new char[num_read_bytes];
    Serial.readBytes(buffer, num_read_bytes);
}

bool TeensyDevice::sd_init()
{
    return SD.begin(BUILTIN_SDCARD);
}

bool TeensyDevice::sd_read(const char* filename, char*& buffer, uint32_t& num_read_bytes) const
{
    File file = SD.open(filename, FILE_READ);
    if (file)
    {
        num_read_bytes = file.size();
        buffer = new char[num_read_bytes];
        file.read(buffer, num_read_bytes);
        file.close();
        return true;
    }
    return false;
}

bool TeensyDevice::sd_write(const char* filename, const char* buffer, const uint32_t num_bytes)
{
    if (SD.exists(filename))
    {
        const bool removed = SD.remove(filename);
        if (!removed)
        {
            return false;
        }
    }
    File file = SD.open(filename, FILE_WRITE);
    if (file)
    {
        file.write(buffer, num_bytes);
        file.close();
        return true;
    }
    return false;
}

void TeensyDevice::start_timer()
{
    start_time = micros();
}

uint32_t TeensyDevice::get_timer_micros()
{
    if (micros() < start_time)
    {
        start_time = micros();
        return 0;
    }
    return micros() - start_time;
}

uint32_t TeensyDevice::milliseconds_since_start() const
{
    return millis();
}

void TeensyDevice::set_led(uint16_t index, uint8_t r, uint8_t g, uint8_t b)
{
    leds[index].r = r;
    leds[index].g = g;
    leds[index].b = b;
}

void TeensyDevice::update_leds()
{
    FastLED.show();
}

void TeensyDevice::mouse_init()
{
    Mouse.begin();
}


void TeensyDevice::mouse_move(int8_t dx, int8_t dy, int8_t wheel)
{
    Mouse.move(dx, dy, wheel);
}


void TeensyDevice::mouse_press(DeviceMouseButton button)
{
    Mouse.press(static_cast<uint8_t>(button));
}


void TeensyDevice::mouse_release(DeviceMouseButton button)
{
    Mouse.release(static_cast<uint8_t>(button));
}

