#include "simulator_device.h"
#include "../core/firmware.h"
#include "simulator_window.h"


int main()
{
    simulator::SimulatorDevice device;
    core::Firmware firmware{device};
    simulator::SimulatorWindow window{device, firmware};
    while (window.is_open())
    {
        window.update();
        firmware.update();
    }

    return 0;
}
