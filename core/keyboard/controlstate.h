#pragma once

namespace core::keyboard
{

struct ControlState
{
    bool increase_brightness = false;
    bool decrease_brightness = false;
    bool toggle_config_mode = false;
    bool next_backlight_mode = false;
};

}
