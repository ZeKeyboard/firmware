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
    virtual void sleep_millis(const int) override { }
    virtual void sleep_micros(const int) override { }
    virtual void gpio_setup(const uint8_t, const PinMode) override { }
    virtual void gpio_write(const uint8_t, const PinState) override { }
    virtual PinState gpio_read(const uint8_t) override { return {}; }

    virtual void set_keyboard_key1(const uint8_t) override { }
    virtual void set_keyboard_key2(const uint8_t) override { }
    virtual void set_keyboard_key3(const uint8_t) override { }
    virtual void set_keyboard_key4(const uint8_t) override { }
    virtual void set_keyboard_key5(const uint8_t) override { }
    virtual void set_keyboard_key6(const uint8_t) override { }
    virtual void set_keyboard_modifier(const uint16_t) override { }
    virtual void set_keyboard_media(const uint16_t) override { }
    virtual void keyboard_send() override { }

    virtual bool serial_data_available() override { return false; }
    virtual void serial_read(char*&, uint32_t&) override { }

    virtual bool sd_init() override { return false; }
    virtual bool sd_read(const char*, char*&, uint32_t&) const override { return false; }
    virtual bool sd_write(const char*, const char*, const uint32_t) override { return false; }

    virtual uint16_t get_keyboard_leds() override { return 0; }

    virtual void serial_begin(const uint32_t) override { }
    virtual void serial_print(const char*) override { }
    virtual void serial_clear() override { }

    virtual void serial_print(uint8_t) override { }
    virtual void serial_print(uint16_t) override { }
    virtual void serial_print(uint32_t) override { }
    virtual void serial_print(int8_t) override { }
    virtual void serial_print(int16_t) override { }
    virtual void serial_print(int32_t) override { }

    virtual void serial_println(const char*) override { }
    virtual void serial_println(uint8_t) override { }
    virtual void serial_println(uint16_t) override { }
    virtual void serial_println(uint32_t) override { }
    virtual void serial_println(int8_t) override { }
    virtual void serial_println(int16_t) override { }
    virtual void serial_println(int32_t) override { }

    virtual void mouse_init() override { }
    virtual void mouse_move(int8_t, int8_t, int8_t) override { }
    virtual void mouse_press(DeviceMouseButton) override { }
    virtual void mouse_release(DeviceMouseButton) override { }

    virtual void start_timer() override { }
    virtual uint32_t get_timer_micros() override { return 0; }

    /**
     * Milliseconds since the device was started.
     */
    virtual uint32_t milliseconds_since_start() const override { return 0; }

    virtual void set_led(uint16_t, uint8_t, uint8_t, uint8_t) override { }
    virtual void update_leds() override { }
    virtual void reboot() override { }

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
    uint32_t milliseconds_since_start() const override
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
        leds_updated = false;
    }
};

}

