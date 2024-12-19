#include "simulator_device.h"
#include "keycodes.h"
#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <mutex>
#include <thread>
#include <iostream>
#include <fstream>

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

void SimulatorDevice::keyboard_send()
{
    bool any_keys_pressed = false;
    for (int i = 0; i < 6; i++)
    {
        if (current_keys[i] != 0)
        {
            any_keys_pressed = true;
            const auto full_code = 0xF000 | current_keys[i];
            std::cout << "Key: " << KEY_CODES.at(full_code);
        }
    }
    if (any_keys_pressed)
    {
        std::cout << std::endl;
    }
}


bool SimulatorDevice::sd_init()
{
    return true;
}


bool SimulatorDevice::sd_read(const char* filename, char*& buffer, uint32_t& num_read_bytes) const
{
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file.is_open())
    {
        return false;
    }
    num_read_bytes = file.tellg();
    file.seekg(0, std::ios::beg);
    buffer = new char[num_read_bytes];
    file.read(buffer, num_read_bytes);
    file.close();
    return true;
}

bool SimulatorDevice::sd_write(const char*, const char*, const uint32_t)
{
    return true;
}

bool SimulatorDevice::serial_data_available()
{
    return std::filesystem::exists("/tmp/Configuration.zkb");
}

void SimulatorDevice::serial_read(char*& buffer, uint32_t& num_read_bytes)
{
    std::ifstream file("/tmp/Configuration.zkb", std::ios::binary | std::ios::ate);
    if (!file.is_open())
    {
        num_read_bytes = 0;
        return;
    }
    num_read_bytes = file.tellg();
    file.seekg(0, std::ios::beg);
    buffer = new char[num_read_bytes];
    file.read(buffer, num_read_bytes);
    file.close();

    std::filesystem::remove("/tmp/Configuration.zkb");
}

void SimulatorDevice::serial_clear()
{
    std::filesystem::remove("/tmp/Configuration.zkb");
}

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
    std::lock_guard<std::mutex> lock(mutex);
    led_colors_r[index] = static_cast<uint8_t>(r * (static_cast<float>(brightness)/255.));
    led_colors_g[index] = static_cast<uint8_t>(g * (static_cast<float>(brightness)/255.));
    led_colors_b[index] = static_cast<uint8_t>(b * (static_cast<float>(brightness)/255.));
}

void SimulatorDevice::update_leds()
{ }

uint32_t SimulatorDevice::milliseconds_since_start() const
{
    return std::chrono::high_resolution_clock::now().time_since_epoch().count() / 1000000;
}

void SimulatorDevice::mouse_move(int8_t dx, int8_t dy, int8_t wheel)
{
    std::cout << "SimulatorDevice::mouse_move(" << (int)dx << ", " << (int)dy << ", " << (int)wheel << ")" << std::endl;
}

void SimulatorDevice::mouse_press(DeviceMouseButton button)
{
    std::cout << "SimulatorDevice::mouse_press(" << (int)button << ")" << std::endl;
}

void SimulatorDevice::mouse_release(DeviceMouseButton button)
{
    std::cout << "SimulatorDevice::mouse_release(" << (int)button << ")" << std::endl;
}

void SimulatorDevice::reboot()
{
    // yes I know, this isn't actually rebooting but it doesn't matter
    std::exit(0);
}

}
