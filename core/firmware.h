#pragma once

#include "../device.h"
#include "keyboard/keyscan.h"

namespace core
{

class Firmware
{

public:
    Firmware(Device& device);
    void update();

private:
    Device& device;
    keyboard::KeyScanner key_scanner;
};

}
