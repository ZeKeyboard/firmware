#include "simulator_device.h"
#include <chrono>
#include <thread>
#include <iostream>

namespace simulator
{

SimulatorDevice::SimulatorDevice()
{
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
}

void SimulatorDevice::gpio_write(const uint8_t pin, const bool value)
{
    std::cout << "Pin " << static_cast<int>(pin) << " set to " << value << std::endl;
}

}
