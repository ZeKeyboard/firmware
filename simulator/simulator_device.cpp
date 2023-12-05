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
        col_state[i] = true;
    }

    for (int i = 0; i < common::constants::NUM_ROWS; i++)
    {
        pin_to_row[common::constants::ROW_PINS[i]] = i;
    }
}

SimulatorDevice::~SimulatorDevice()
{
}

void SimulatorDevice::sleep_millis(const int millis)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(millis));
}

void SimulatorDevice::sleep_micros(const int micros)
{
    std::this_thread::sleep_for(std::chrono::microseconds(micros));
}

void SimulatorDevice::gpio_setup(const uint8_t pin, const PinMode mode)
{
    std::lock_guard<std::mutex> lock(mutex);
    std::cout << "SimulatorDevice::gpio_setup(" << (int)pin << ", " << (int)mode << ")" << std::endl;
}

void SimulatorDevice::gpio_write(const uint8_t pin, const bool value)
{
    std::lock_guard<std::mutex> lock(mutex);
    std::cout << "SimulatorDevice::gpio_write(" << (int)pin << ", " << (int)value << ")" << std::endl;
    if (pin_to_col.count(pin))
    {
        col_state[pin_to_col[pin]] = value;
    }
}

bool SimulatorDevice::gpio_read(const uint8_t pin)
{
    std::lock_guard<std::mutex> lock(mutex);
    if (pin_to_row.count(pin) == 0)
    {
        return true;
    }

    for (int i = 0; i < common::constants::NUM_ROWS; i++)
    {
        for (int j = 0; j < common::constants::NUM_COLS; j++)
        {
            if (input_state[i][j] && !col_state[j])
            {
                return false;
            }
        }
    }
    return true;
}

void SimulatorDevice::set_pressed_row_and_col(const int row, const int col, const bool pressed)
{
    std::lock_guard<std::mutex> lock(mutex);
    input_state[row][col] = pressed;
}

}
