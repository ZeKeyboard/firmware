#pragma once

#include "../device.h"
#include <mutex>
#include "../common/constants.h"
#include <map>


namespace simulator
{

class SimulatorDevice : public Device
{
public:
    SimulatorDevice();
    ~SimulatorDevice();

    virtual void sleep_millis(const int millis) override;
    virtual void sleep_micros(const int micros) override;
    virtual void gpio_setup(const uint8_t pin, const PinMode mode) override;
    virtual void gpio_write(const uint8_t pin, const PinState value) override;
    virtual PinState gpio_read(const uint8_t pin) override;

    virtual void set_keyboard_key1(const uint8_t) override;
    virtual void set_keyboard_key2(const uint8_t) override;
    virtual void set_keyboard_key3(const uint8_t) override;
    virtual void set_keyboard_key4(const uint8_t) override;
    virtual void set_keyboard_key5(const uint8_t) override;
    virtual void set_keyboard_key6(const uint8_t) override;
    virtual void set_keyboard_modifier(const uint16_t modifier) override;
    virtual void set_keyboard_media(const uint16_t media) override;
    virtual void keyboard_send() override;

    virtual uint16_t get_keyboard_leds() override
    {
        return leds;
    }

    virtual void serial_begin(const uint32_t) override { }
    virtual void serial_print(const char*) override { }

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

    void set_pressed_row_and_col(const int row, const int col, const bool pressed);

    virtual void start_timer() override;
    virtual uint32_t get_timer_micros() override;
    virtual uint32_t millis() const override;

    virtual void set_led(uint16_t index, uint8_t r, uint8_t g, uint8_t b) override;
    virtual void update_leds() override;

    uint8_t last_read_col;
    bool row_state[common::constants::NUM_ROWS];

    uint8_t current_keys[common::constants::MAX_KEYREPORT_KEYS];
    uint8_t current_modifier;
    uint8_t current_media;

private:
    uint32_t start_time;

    uint16_t leds;
    std::mutex mutex;

    bool input_state[common::constants::NUM_ROWS][common::constants::NUM_COLS];

    std::map<uint8_t, uint8_t> pin_to_col;
    std::map<uint8_t, uint8_t> pin_to_row;
};

}
