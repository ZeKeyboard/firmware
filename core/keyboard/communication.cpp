#include "communication.h"
#include <utility>

namespace core::keyboard::communication
{

void send_mouse_commands(MouseState& mouse_state, Device& device)
{
    const auto movement = mouse_state.get_movement();
    if (movement.moving)
    {
        device.mouse_move(movement.dx, movement.dy, movement.wheel);
    }

    const auto left_button_state = mouse_state.get_button_state(MouseButton::LEFT);
    const auto middle_button_state = mouse_state.get_button_state(MouseButton::MIDDLE);
    const auto right_button_state = mouse_state.get_button_state(MouseButton::RIGHT);

    const auto buttons = {
        std::make_pair(DeviceMouseButton::LEFT, left_button_state),
        std::make_pair(DeviceMouseButton::MIDDLE, middle_button_state),
        std::make_pair(DeviceMouseButton::RIGHT, right_button_state)
    };

    for (const auto&[button_code, button_state] : buttons)
    {
        switch (button_state)
        {
            case ButtonState::JUST_PRESSED:
                device.mouse_press(button_code);
                break;
            case ButtonState::JUST_RELEASED:
                device.mouse_release(button_code);
                break;
            default:
                break;
        }
    }
}


void send_key_report(KeyQueue& key_queue, Device& device)
{
    if (key_queue.size() > 0)
    {
        const KeyReport report = key_queue.front();
        for (unsigned i = 0; i < common::constants::MAX_KEYREPORT_KEYS; ++i)
        {
            const auto code = i < report.num_keys ? report.keys[i] : 0;
            device.set_keyboard_key_by_index(i, code);
        }
        device.set_keyboard_modifier(report.modifier);
        device.set_keyboard_media(report.media);
        device.keyboard_send();
        key_queue.pop();
    }
    else
    {
        for (unsigned i = 0; i < common::constants::MAX_KEYREPORT_KEYS; ++i)
        {
            device.set_keyboard_key_by_index(i, 0);
        }
        device.set_keyboard_modifier(0);
        device.set_keyboard_media(0);
        device.keyboard_send();
    }
}

}
