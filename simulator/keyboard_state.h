#pragma once

#include <array>
#include <SFML/Graphics.hpp>

#include "../common/key_properties.h"
#include "../common/constants.h"


namespace simulator
{

struct Key
{
    bool pressed;
    const common::KeyDescription* description;
};

class KeyboardState
{
public:
    KeyboardState();

    void draw(sf::RenderWindow& window);

    std::array<Key, common::constants::TOTAL_NUM_KEYS> keys;
};

}
