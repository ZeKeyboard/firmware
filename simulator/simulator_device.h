#pragma once

#include "../device.h"
#include <mutex>
#include "../common/constants.h"
#include <map>


namespace simulator
{

const int SLEEP_MULTIPLIER = 100;

class SimulatorDevice : public Device
{
public:
    SimulatorDevice();
    ~SimulatorDevice();

    virtual void sleep_millis(const int millis) override;
    virtual void sleep_micros(const int micros) override;
    virtual void gpio_setup(const uint8_t pin, const PinMode mode) override;
    virtual void gpio_write(const uint8_t pin, const bool value) override;
    virtual bool gpio_read(const uint8_t pin) override;

    virtual void set_keyboard_key1(const uint8_t) override;
    virtual void set_keyboard_key2(const uint8_t) override;
    virtual void set_keyboard_key3(const uint8_t) override;
    virtual void set_keyboard_key4(const uint8_t) override;
    virtual void set_keyboard_key5(const uint8_t) override;
    virtual void set_keyboard_key6(const uint8_t) override;

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

    uint8_t last_read_col;
    bool row_state[common::constants::NUM_ROWS];

private:
    uint16_t leds;
    std::mutex mutex;

    bool input_state[common::constants::NUM_ROWS][common::constants::NUM_COLS];

    std::map<uint8_t, uint8_t> pin_to_col;
    std::map<uint8_t, uint8_t> pin_to_row;
};

}
