#pragma once

#include "../device.h"
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
};

}
