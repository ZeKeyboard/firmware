#pragma once

#include <SFML/Graphics.hpp>
#include "../device.h"
#include "keyboard_state.h"


namespace simulator
{

class SimulatorWindow
{

public:
    SimulatorWindow(Device& device);

    void update();

    bool is_open() const;

private:
    void draw();

    sf::RenderWindow window;
    Device& device;
    KeyboardState keyboard_state;
};

}
