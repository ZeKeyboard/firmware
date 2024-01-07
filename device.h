#pragma once

#include <stdint.h>

enum class PinMode
{
    IN = 0,
    OUT = 1,
    IN_PULLUP = 2,
    IN_PULLDOWN = 3,
    OUT_OPENDRAIN = 4,
    IN_DISABLE = 5,
};

enum class PinState
{
    LEVEL_LOW = 0,
    LEVEL_HIGH = 1,
};

class Device
{
public:
    virtual void sleep_millis(const int millis) = 0;
    virtual void sleep_micros(const int micros) = 0;
    virtual void gpio_setup(const uint8_t pin, const PinMode mode) = 0;
    virtual void gpio_write(const uint8_t pin, const PinState value) = 0;
    virtual PinState gpio_read(const uint8_t pin) = 0;

    virtual void set_keyboard_key1(const uint8_t code) = 0;
    virtual void set_keyboard_key2(const uint8_t code) = 0;
    virtual void set_keyboard_key3(const uint8_t code) = 0;
    virtual void set_keyboard_key4(const uint8_t code) = 0;
    virtual void set_keyboard_key5(const uint8_t code) = 0;
    virtual void set_keyboard_key6(const uint8_t code) = 0;
    virtual void set_keyboard_modifier(const uint16_t modifier) = 0;
    virtual void set_keyboard_media(const uint16_t media) = 0;
    virtual void keyboard_send() = 0;

    // TODO may need more work
    // virtual bool sd_read(const char* filename, char* buffer, const uint32_t buffer_size) = 0;

    virtual uint16_t get_keyboard_leds() = 0;

    virtual void serial_begin(const uint32_t baud) = 0;
    virtual void serial_print(const char* str) = 0;

    virtual void serial_print(uint8_t val) = 0;
    virtual void serial_print(uint16_t val) = 0;
    virtual void serial_print(uint32_t val) = 0;
    virtual void serial_print(int8_t val) = 0;
    virtual void serial_print(int16_t val) = 0;
    virtual void serial_print(int32_t val) = 0;

    virtual void serial_println(const char* str) = 0;
    virtual void serial_println(uint8_t val) = 0;
    virtual void serial_println(uint16_t val) = 0;
    virtual void serial_println(uint32_t val) = 0;
    virtual void serial_println(int8_t val) = 0;
    virtual void serial_println(int16_t val) = 0;
    virtual void serial_println(int32_t val) = 0;

    virtual void start_timer() = 0;
    virtual uint32_t get_timer_micros() = 0;

    /**
     * Milliseconds since the device was started.
     */
    virtual uint32_t millis() const = 0;

    inline void set_keyboard_key_by_index(const uint8_t index, const uint8_t code)
    {
        // This is a bit of a hack, but it works.
        if (index == 0)
        {
            set_keyboard_key1(code);
        }
        else if (index == 1)
        {
            set_keyboard_key2(code);
        }
        else if (index == 2)
        {
            set_keyboard_key3(code);
        }
        else if (index == 3)
        {
            set_keyboard_key4(code);
        }
        else if (index == 4)
        {
            set_keyboard_key5(code);
        }
        else if (index == 5)
        {
            set_keyboard_key6(code);
        }
    }
};
