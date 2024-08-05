#include "mouse.h"

namespace core::keyboard
{

MouseMovement MouseState::get_movement() const
{
    if (dx == 0 && dy == 0 && wheel == 0)
    {
        return {};
    }

    const int8_t acceleration = accelerated ? mouse_acceleration : 1;

    return {
        true,
        static_cast<int8_t>(dx * mouse_speed * acceleration),
        static_cast<int8_t>(dy * mouse_speed * acceleration),
        static_cast<int8_t>(wheel * MOUSE_WHEEL_DEFAULT_SPEED  * acceleration)
    };
}


void MouseState::set_buttons(const bool left, const bool middle, const bool right)
{
    prev_left_button = left_button;
    prev_middle_button = middle_button;
    prev_right_button = right_button;

    left_button = left;
    middle_button = middle;
    right_button = right;
}


ButtonState MouseState::get_button_state(const MouseButton button) const
{
    switch (button)
    {
        case MouseButton::LEFT:
            return get_button_state(left_button, prev_left_button);
        case MouseButton::MIDDLE:
            return get_button_state(middle_button, prev_middle_button);
        case MouseButton::RIGHT:
            return get_button_state(right_button, prev_right_button);
        default:
            return ButtonState::RELEASED;
    }
}


ButtonState MouseState::get_button_state(const bool current, const bool previous) const
{
    if (current && previous)
    {
        return ButtonState::PRESSED;
    }
    else if (current && !previous)
    {
        return ButtonState::JUST_PRESSED;
    }
    else if (!current && previous)
    {
        return ButtonState::JUST_RELEASED;
    }
    else
    {
        return ButtonState::RELEASED;
    }
}

}
