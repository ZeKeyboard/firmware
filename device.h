#pragma once

#include <stdint.h>

enum class PinMode
{
    IN = 0,
    OUT = 1,
    IN_PULLUP = 2,
    IN_PULLDOWN = 3,
    OUT_OPENDRAIN = 4,
    IN_DISABLE = 5,
};

class Device
{
public:
    virtual void sleep_millis(const int millis) = 0;
    virtual void sleep_micros(const int micros) = 0;
    virtual void gpio_setup(const uint8_t pin, const PinMode mode) = 0;
    virtual void gpio_write(const uint8_t pin, const bool value) = 0;
    virtual bool gpio_read(const uint8_t pin) = 0;
};
