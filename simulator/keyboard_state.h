#pragma once

#include <array>
#include <SFML/Graphics.hpp>
#include <map>

#include "../common/key_properties.h"
#include "../core/keyboard/keymap.h"
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
    KeyboardState(SimulatorDevice& device, const core::keyboard::KeyMap& key_map, const sf::Font& font);

    void handle_input(sf::RenderWindow& window);

    void draw(sf::RenderWindow& window);

private:
    std::array<Key, common::constants::TOTAL_NUM_KEYS> keys;
    SimulatorDevice& device;
    const sf::Font& font;
    const core::keyboard::KeyMap& keymap;

    void draw_row_and_col_state(
        sf::RenderWindow& window,
        const int row,
        const int col,
        const float x,
        const float y);
};

}
