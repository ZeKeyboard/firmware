#include "keyscan.h"
#include "../util/array_utils.h"


namespace core::keyboard
{

const uint8_t READ_DELAY_MICROS = 5;

void KeyboardScanResult::try_add_pressed_key(const common::KeyDescription* key)
{
    if (num_just_pressed < common::constants::MAX_JUST_PRESSED_KEYS)
    {
        just_pressed[num_just_pressed++] = key;
    }
}

void KeyboardScanResult::update()
{
    const common::KeyDescription* old_pressed[common::constants::TOTAL_NUM_KEYS];
    util::array_copy(pressed, old_pressed, num_pressed);

    int new_just_released = 0;
    util::array_subtract(old_pressed, num_pressed, just_pressed, num_just_pressed, just_released, new_just_released);
    num_just_released = new_just_released;

    util::array_copy(just_pressed, pressed, num_just_pressed);
    num_pressed = num_just_pressed;

    const common::KeyDescription* old_just_pressed[common::constants::TOTAL_NUM_KEYS];
    util::array_copy(just_pressed, old_just_pressed, num_just_pressed);

    int new_just_pressed = 0;
    util::array_subtract(old_just_pressed, num_just_pressed, previously_pressed, num_previously_pressed, just_pressed, new_just_pressed);
    num_just_pressed = new_just_pressed;
}

void KeyboardScanResult::reset_just_pressed()
{
    num_previously_pressed = num_pressed;
    for (int i = 0; i < num_pressed; ++i)
    {
        previously_pressed[i] = just_pressed[i];
        just_pressed[i] = nullptr;
    }
    num_just_pressed = 0;
}

KeyScanner::KeyScanner(Device& device)
    : device{device}
{
    for (uint8_t row = 0; row < common::constants::NUM_ROWS; ++row)
    {
        const auto row_pin = common::constants::ROW_PINS[row];
        device.gpio_setup(row_pin, PinMode::OUT);
        device.gpio_write(row_pin, PinState::LEVEL_HIGH);
    }

    for (uint8_t col = 0; col < common::constants::NUM_COLS; ++col)
    {
        const auto col_pin = common::constants::COL_PINS[col];
        device.gpio_setup(col_pin, PinMode::IN_PULLUP);
    }
}

void KeyScanner::scan(KeyboardScanResult& result)
{
    result.reset_just_pressed();
    for (uint8_t row = 0; row < common::constants::NUM_ROWS; ++row)
    {
        const auto row_pin = common::constants::ROW_PINS[row];
        device.gpio_write(row_pin, PinState::LEVEL_LOW);
        device.sleep_micros(READ_DELAY_MICROS);

        for (uint8_t col = 0; col < common::constants::NUM_COLS; ++col)
        {
            const auto key_description = common::constants::KEY_PROPERTIES_BY_ROW_COL[row][col];
            if (key_description != nullptr)
            {
                const auto col_pin = common::constants::COL_PINS[col];
                const auto pressed = device.gpio_read(col_pin) == PinState::LEVEL_LOW;

                if (pressed)
                {
                    result.try_add_pressed_key(key_description);
                }
            }
        }
    }
    result.update();
}

}
