#pragma once

#include <array>
#include <SFML/Graphics.hpp>
#include <map>

#include "../common/key_properties.h"
#include "../common/constants.h"
#include "simulator_device.h"


namespace simulator
{

struct Key
{
    bool pressed;
    bool hovered;
    const common::KeyDescription* description;
};

class KeyboardState
{
public:
    KeyboardState(SimulatorDevice& device);

    void handle_input(sf::RenderWindow& window);

    void draw(sf::RenderWindow& window);

private:
    std::array<Key, common::constants::TOTAL_NUM_KEYS> keys;
    SimulatorDevice& device;

    void draw_row_and_col_state(
        sf::RenderWindow& window,
        const int row,
        const int col,
        const float x,
        const float y);
};

}
