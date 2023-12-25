#pragma once

#include <SFML/Graphics.hpp>
#include "../device.h"
#include "Graphics/Font.hpp"
#include "keyboard_state.h"
#include "../core/firmware.h"


namespace simulator
{

class SimulatorWindow
{

public:
    SimulatorWindow(SimulatorDevice& device, core::Firmware& firmware);

    void update();

    bool is_open() const;

private:
    void draw();

    void draw_firmware();

    sf::RenderWindow window;
    sf::Font font;
    Device& device;
    core::Firmware& firmware;
    KeyboardState keyboard_state;
};

}
