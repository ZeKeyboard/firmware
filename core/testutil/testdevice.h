#pragma once

#include "../../device.h"
#include "../backlight/color.h"
#include "../../common/constants.h"

namespace testutil
{

/**
 * Device implementation for testing purposes.
 */
class TestDeviceBase : public Device
{
public:
    virtual void sleep_millis(const int) { }
    virtual void sleep_micros(const int) { }
    virtual void gpio_setup(const uint8_t, const PinMode) { }
    virtual void gpio_write(const uint8_t, const PinState) { }
    virtual PinState gpio_read(const uint8_t) { return {}; }

    virtual void set_keyboard_key1(const uint8_t) { }
    virtual void set_keyboard_key2(const uint8_t) { }
    virtual void set_keyboard_key3(const uint8_t) { }
    virtual void set_keyboard_key4(const uint8_t) { }
    virtual void set_keyboard_key5(const uint8_t) { }
    virtual void set_keyboard_key6(const uint8_t) { }
    virtual void set_keyboard_modifier(const uint16_t) { }
    virtual void set_keyboard_media(const uint16_t) { }
    virtual void keyboard_send() { }

    // TODO may need more work
    // virtual bool sd_read(const char* filename, char* buffer, const uint32_t buffer_size) { }

    virtual uint16_t get_keyboard_leds() { return 0; }

    virtual void serial_begin(const uint32_t) { }
    virtual void serial_print(const char*) { }

    virtual void serial_print(uint8_t) { }
    virtual void serial_print(uint16_t) { }
    virtual void serial_print(uint32_t) { }
    virtual void serial_print(int8_t) { }
    virtual void serial_print(int16_t) { }
    virtual void serial_print(int32_t) { }

    virtual void serial_println(const char*) { }
    virtual void serial_println(uint8_t) { }
    virtual void serial_println(uint16_t) { }
    virtual void serial_println(uint32_t) { }
    virtual void serial_println(int8_t) { }
    virtual void serial_println(int16_t) { }
    virtual void serial_println(int32_t) { }

    virtual void start_timer() { }
    virtual uint32_t get_timer_micros() { return 0; }

    /**
     * Milliseconds since the device was started.
     */
    virtual uint32_t millis() const { return 0; }

    virtual void set_led(uint16_t, uint8_t, uint8_t, uint8_t) { }
    virtual void update_leds() { }

};

class TestTimerLEDDevice : public TestDeviceBase
{
public:
    TestTimerLEDDevice()
    {
        for (int i = 0; i < common::constants::TOTAL_NUM_LEDS; ++i)
        {
            led_colors_r[i] = 0;
            led_colors_g[i] = 0;
            led_colors_b[i] = 0;
        }
    }

    uint32_t current_millis = 0;
    uint32_t millis() const override
    {
        return current_millis;
    }

    bool leds_updated = true;
    void update_leds() override
    {
        leds_updated = true;
    }

    uint8_t led_colors_r[common::constants::TOTAL_NUM_LEDS];
    uint8_t led_colors_g[common::constants::TOTAL_NUM_LEDS];
    uint8_t led_colors_b[common::constants::TOTAL_NUM_LEDS];

    void set_led(uint16_t index, uint8_t r, uint8_t g, uint8_t b) override
    {
        led_colors_r[index] = r;
        led_colors_g[index] = g;
        led_colors_b[index] = b;
    }
};

}

