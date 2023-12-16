#include "simulator_device.h"
#include <chrono>
#include <mutex>
#include <thread>
#include <iostream>

namespace simulator
{

SimulatorDevice::SimulatorDevice()
{
    for (int i = 0; i < common::constants::NUM_ROWS; i++)
    {
        for (int j = 0; j < common::constants::NUM_COLS; j++)
        {
            input_state[i][j] = false;
        }
    }


    for (int i = 0; i < common::constants::NUM_COLS; i++)
    {
        pin_to_col[common::constants::COL_PINS[i]] = i;
    }

    for (int i = 0; i < common::constants::NUM_ROWS; i++)
    {
        pin_to_row[common::constants::ROW_PINS[i]] = i;
        row_state[i] = true;
    }
}

SimulatorDevice::~SimulatorDevice()
{
}

void SimulatorDevice::sleep_millis(const int millis)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(millis * SLEEP_MULTIPLIER));
}

void SimulatorDevice::sleep_micros(const int micros)
{
    std::this_thread::sleep_for(std::chrono::microseconds(micros * SLEEP_MULTIPLIER));
}

void SimulatorDevice::gpio_setup(const uint8_t pin, const PinMode mode)
{
    std::lock_guard<std::mutex> lock(mutex);
    std::cout << "SimulatorDevice::gpio_setup(" << (int)pin << ", " << (int)mode << ")" << std::endl;
}

void SimulatorDevice::gpio_write(const uint8_t pin, const PinState value)
{
    std::lock_guard<std::mutex> lock(mutex);
    std::cout << "SimulatorDevice::gpio_write(" << (int)pin << ", " << (int)value << ")" << std::endl;
    if (pin_to_row.count(pin))
    {
        row_state[pin_to_row[pin]] = (bool)value;
    }
}

PinState SimulatorDevice::gpio_read(const uint8_t pin)
{
    std::lock_guard<std::mutex> lock(mutex);
    if (pin_to_col.count(pin) == 0)
    {
        return PinState::LEVEL_HIGH;
    }
    last_read_col = pin_to_col[pin];

    for (int row = 0; row < common::constants::NUM_ROWS; row++)
    {
        for (int col = 0; col < common::constants::NUM_COLS; col++)
        {
            if (input_state[row][col] && !row_state[row])
            {
                return PinState::LEVEL_LOW;
            }
        }
    }
    return PinState::LEVEL_HIGH;
}

void SimulatorDevice::set_pressed_row_and_col(const int row, const int col, const bool pressed)
{
    std::lock_guard<std::mutex> lock(mutex);
    input_state[row][col] = pressed;
}

void SimulatorDevice::set_keyboard_key1(const uint8_t) { }
void SimulatorDevice::set_keyboard_key2(const uint8_t) { }
void SimulatorDevice::set_keyboard_key3(const uint8_t) { }
void SimulatorDevice::set_keyboard_key4(const uint8_t) { }
void SimulatorDevice::set_keyboard_key5(const uint8_t) { }
void SimulatorDevice::set_keyboard_key6(const uint8_t) { }

}
