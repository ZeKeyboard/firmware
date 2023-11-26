#include "simulator_device.h"
#include "../core/firmware.h"


int main()
{
    SimulatorDevice device;
    core::Firmware firmware(device);
    firmware.init();
    while (true)
    {
        firmware.update();
    }

    return 0;
}
