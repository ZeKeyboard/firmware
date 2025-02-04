#pragma once

#include "../../common/constants.h"
#include "../../common/key_properties.h"
#include "../../device.h"

namespace core::keyboard
{

struct KeyboardScanResult
{
    uint8_t num_just_pressed = 0;
    const common::KeyDescription* just_pressed[common::constants::MAX_JUST_PRESSED_KEYS];

    uint8_t num_just_released = 0;
    const common::KeyDescription* just_released[common::constants::MAX_JUST_PRESSED_KEYS];

    uint8_t num_pressed = 0;
    const common::KeyDescription* pressed[common::constants::TOTAL_NUM_KEYS];

    uint8_t num_previously_pressed = 0;
    const common::KeyDescription* previously_pressed[common::constants::MAX_JUST_PRESSED_KEYS];

    void try_add_pressed_key(const common::KeyDescription* key);
    void reset_just_pressed();
    void update();
    bool are_any_keys_pressed() const;
};


class KeyScanner
{
public:
    KeyScanner(Device& device);

    void scan(KeyboardScanResult& result);

private:
    Device& device;
};

}
