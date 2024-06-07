#pragma once

#include <cstdint>


namespace core::keyboard
{

enum class MouseButton
{
    LEFT,
    MIDDLE,
    RIGHT
};


enum class ButtonState
{
    JUST_PRESSED,
    PRESSED,
    JUST_RELEASED,
    RELEASED
};


struct MouseMovement
{
    bool moving = false;
    int8_t dx = 0;
    int8_t dy = 0;
    int8_t wheel = 0;
};


// TODO make configurable
const int8_t MOUSE_ACCELERATION_AMOUNT = 2;

const int8_t MOUSE_MOVE_DEFAULT_SPEED = 1;
const int8_t MOUSE_WHEEL_DEFAULT_SPEED = 1;

class MouseState
{
public:
    void set_buttons(const bool left, const bool middle, const bool right);

    ButtonState get_button_state(const MouseButton button) const;
    MouseMovement get_movement() const;

    void set_dx(const int8_t dx) { this->dx = dx; }
    void set_dy(const int8_t dy) { this->dy = dy; }
    void set_wheel(const int8_t wheel) { this->wheel = wheel; }

    bool accelerated = false;

    void reset()
    {
        dx = 0;
        dy = 0;
        wheel = 0;
    }

private:
    int8_t dx = 0;
    int8_t dy = 0;
    int8_t wheel = 0;

    ButtonState get_button_state(const bool current, const bool previous) const;

    bool left_button = false;
    bool middle_button = false;
    bool right_button = false;

    bool prev_left_button = false;
    bool prev_middle_button = false;
    bool prev_right_button = false;
};

}
