#include "simulator_device.h"
#include "../core/firmware.h"
#include "simulator_window.h"
#include <thread>


void window_thread(simulator::SimulatorWindow& window)
{
    while (window.is_open())
    {
        window.update();
    }
}


void firmware_thread(core::Firmware& firmware)
{
    firmware.init();

    while (true)
    {
        firmware.update();
    }
}


int main()
{
    simulator::SimulatorDevice device;
    simulator::SimulatorWindow window{device};
    core::Firmware firmware{device};

    std::thread window_thread{::window_thread, std::ref(window)};
    std::thread firmware_thread{::firmware_thread, std::ref(firmware)};
    window_thread.join();
    firmware_thread.join();

    return 0;
}
