#pragma once

#include "device.h"

class TeensyDevice : public Device
{
public:
    virtual void sleep_millis(const int millis) override;
    virtual void sleep_micros(const int micros) override;
    virtual void gpio_setup(const uint8_t pin, const PinMode mode) override;
    virtual void gpio_write(const uint8_t pin, const bool value) override;
    virtual bool gpio_read(const uint8_t pin) override;

    virtual void set_keyboard_key1(const uint8_t code) override;
    virtual void set_keyboard_key2(const uint8_t code) override;
    virtual void set_keyboard_key3(const uint8_t code) override;
    virtual void set_keyboard_key4(const uint8_t code) override;
    virtual void set_keyboard_key5(const uint8_t code) override;
    virtual void set_keyboard_key6(const uint8_t code) override;

    virtual uint16_t get_keyboard_leds() override;

    virtual void serial_begin(const uint32_t baud) override;
    virtual void serial_print(const char* str) override;

    virtual void serial_print(uint8_t val) override;
    virtual void serial_print(uint16_t val) override;
    virtual void serial_print(uint32_t val) override;
    virtual void serial_print(int8_t val) override;
    virtual void serial_print(int16_t val) override;
    virtual void serial_print(int32_t val) override;

    virtual void serial_println(const char* str) override;
    virtual void serial_println(uint8_t val) override;
    virtual void serial_println(uint16_t val) override;
    virtual void serial_println(uint32_t val) override;
    virtual void serial_println(int8_t val) override;
    virtual void serial_println(int16_t val) override;
    virtual void serial_println(int32_t val) override;
};
