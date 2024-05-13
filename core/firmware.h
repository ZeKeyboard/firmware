#pragma once

#include "../device.h"
#include "backlight/backlight.h"
#include "backlight/schemes/wave.h"
#include "keyboard/keymap.h"
#include "keyboard/keyscan.h"

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

    bool loaded_keymap = false;

    // Backlight schemes
    backlight::schemes::Wave wave;

    static constexpr int NUM_SCHEMES = 1;
    backlight::schemes::Scheme* schemes[NUM_SCHEMES] =
    {
        &wave
    };

    backlight::Backlight backlight;
};

}
