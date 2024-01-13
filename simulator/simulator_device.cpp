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
        if (input_state[row][last_read_col] && !row_state[row])
        {
            return PinState::LEVEL_LOW;
        }
    }
    return PinState::LEVEL_HIGH;
}

void SimulatorDevice::set_pressed_row_and_col(const int row, const int col, const bool pressed)
{
    std::lock_guard<std::mutex> lock(mutex);
    input_state[row][col] = pressed;
}

void SimulatorDevice::set_keyboard_key1(const uint8_t code)
{
    current_keys[0] = code;
}
void SimulatorDevice::set_keyboard_key2(const uint8_t code)
{
    current_keys[1] = code;
}
void SimulatorDevice::set_keyboard_key3(const uint8_t code)
{
    current_keys[2] = code;
}
void SimulatorDevice::set_keyboard_key4(const uint8_t code)
{
    current_keys[3] = code;
}
void SimulatorDevice::set_keyboard_key5(const uint8_t code)
{
    current_keys[4] = code;
}
void SimulatorDevice::set_keyboard_key6(const uint8_t code)
{
    current_keys[5] = code;
}
void SimulatorDevice::set_keyboard_modifier(const uint16_t modifier)
{
    this->current_modifier = modifier;
}
void SimulatorDevice::set_keyboard_media(const uint16_t media)
{
    this->current_media = media;
}
void SimulatorDevice::keyboard_send() { }

void SimulatorDevice::start_timer()
{
    start_time = std::chrono::high_resolution_clock::now().time_since_epoch().count();
}

uint32_t SimulatorDevice::get_timer_micros()
{
    return (std::chrono::high_resolution_clock::now().time_since_epoch().count() - start_time) / 1000;
}

void SimulatorDevice::set_led(uint16_t index, uint8_t r, uint8_t g, uint8_t b)
{
    // TODO implement
}

void SimulatorDevice::update_leds()
{
    // TODO implement
}

uint32_t SimulatorDevice::millis() const
{
    return std::chrono::high_resolution_clock::now().time_since_epoch().count() / 1000000;
}

}
