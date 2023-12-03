#include "simulator_device.h"
#include "../core/firmware.h"
#include "simulator_window.h"


int main()
{
    simulator::SimulatorDevice device;
    simulator::SimulatorWindow window{device};
    core::Firmware firmware(device);
    firmware.init();

    while (window.is_open())
    {
        firmware.update();
        window.update();
    }

    return 0;
}
