#pragma once

#include "../device.h"
#include "backlight/backlight.h"
#include "backlight/schemes/gameoflife.h"
#include "backlight/schemes/lights.h"
#include "backlight/schemes/wave.h"
#include "backlight/schemes/water.h"
#include "keyboard/controlstate.h"
#include "keyboard/hardware_config_button.h"
#include "keyboard/keymap.h"
#include "keyboard/keyscan.h"
#include "keyboard/settings.h"

namespace simulator { class SimulatorWindow; }

namespace core
{

class Firmware
{
    friend class simulator::SimulatorWindow;

public:
    Firmware(Device& device);
    void update();

private:
    Device& device;
    keyboard::KeyScanner key_scanner;
    keyboard::KeyQueue key_queue;
    keyboard::KeyMap keymap;
    keyboard::KeyboardScanResult keyboard_scan_result;
    keyboard::MouseState mouse_state;
    keyboard::Settings settings;
    keyboard::HardwareConfigButton config_button;

    bool loaded_keymap = false;

    // Backlight schemes
    backlight::schemes::Wave wave;
    backlight::schemes::GameOfLife game_of_life;
    backlight::schemes::Lights lights;
    backlight::schemes::Water water;

    static constexpr int NUM_SCHEMES = 4;
    backlight::schemes::Scheme* schemes[NUM_SCHEMES] =
    {
        &wave,
        &water,
        &game_of_life,
        &lights
    };

    backlight::Backlight backlight;

    bool configure_mode = false;
    bool last_configure_mode = false;

    void process_control_inputs(keyboard::ControlState& control);
};

}
