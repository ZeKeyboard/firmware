#pragma once

#include "../device.h"
#include "backlight/backlight.h"
#include "backlight/schemes/wave.h"
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

    static constexpr int NUM_SCHEMES = 1;
    backlight::schemes::Scheme* schemes[NUM_SCHEMES] =
    {
        &wave
    };

    backlight::Backlight backlight;

    bool configure_mode = false;
    bool last_configure_mode = false;
};

}
