#include "hardware_config_button.h"

namespace core::keyboard {

const int CONFIG_PIN = 14;

HardwareConfigButton::HardwareConfigButton(Device& device) : device{device}
{
    device.gpio_setup(CONFIG_PIN, PinMode::IN_PULLUP);
}

void HardwareConfigButton::update()
{
    prev_state = curr_state;
    curr_state = device.gpio_read(CONFIG_PIN) == PinState::LEVEL_LOW;
}

bool HardwareConfigButton::state() const
{
    return curr_state && !prev_state;
}

}
