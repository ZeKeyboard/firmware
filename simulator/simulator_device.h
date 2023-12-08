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

    void set_pressed_row_and_col(const int row, const int col, const bool pressed);

    // TODO access this in a thread-safe way
    uint8_t last_read_col;
    bool row_state[common::constants::NUM_ROWS];

private:
    std::mutex mutex;

    bool input_state[common::constants::NUM_ROWS][common::constants::NUM_COLS];

    std::map<uint8_t, uint8_t> pin_to_col;
    std::map<uint8_t, uint8_t> pin_to_row;
};

}
