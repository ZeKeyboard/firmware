#include "firmware.h"
#include "../common/constants.h"

namespace core
{

Firmware::Firmware(Device& device) : device{device}
{ }

void Firmware::init()
{
    // TODO temporary, just to test the simulator
    device.gpio_setup(13, PinMode::OUT);
    for (uint8_t row = 0; row < common::constants::NUM_ROWS; row++)
    {
        const auto row_pin = common::constants::ROW_PINS[row];
        device.gpio_setup(row_pin, PinMode::OUT);
        device.gpio_write(row_pin, true);
    }
    for (uint8_t col = 0; col < common::constants::NUM_COLS; col++)
    {
        const auto col_pin = common::constants::COL_PINS[col];
        device.gpio_setup(col_pin, PinMode::IN_PULLDOWN);
    }
}

void Firmware::update()
{
    // TODO temporary, just to test the simulator
    for (uint8_t row = 0; row < common::constants::NUM_ROWS; ++row)
    {
        const auto row_pin = common::constants::ROW_PINS[row];
        device.gpio_write(row_pin, false);
        for (uint8_t col = 0; col < common::constants::NUM_COLS; ++col)
        {
            const auto col_pin = common::constants::COL_PINS[col];
            const auto pressed = device.gpio_read(col_pin);
            device.sleep_millis(1);
        }
        device.gpio_write(row_pin, true);
    }
}

}
