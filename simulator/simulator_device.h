#pragma once

#include "../device.h"

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
    virtual void gpio_write(const uint8_t pin, const bool value) override;
private:
};

}
