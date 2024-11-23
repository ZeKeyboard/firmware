#pragma once
#include "../../device.h"

namespace core::keyboard {

class HardwareConfigButton
{
public:
    HardwareConfigButton(Device& device);
    void update();
    bool state() const;

private:
    bool curr_state;
    bool prev_state;
    Device& device;
};

}
