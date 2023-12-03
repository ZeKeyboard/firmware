#pragma once

#include "../device.h"

namespace core
{

class Firmware
{

public:
    Firmware(Device& device);
    void init();
    void update();

private:
    Device& device;
};

}
