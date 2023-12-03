#include "keyboard_state.h"


namespace simulator
{

const int KEY_SIZE = 80;
const int KEY_PADDING = 20;

KeyboardState::KeyboardState()
{
    for (unsigned i = 0; i < common::constants::TOTAL_NUM_KEYS; ++i)
    {
        keys[i] = { 0, &common::constants::KEY_PROPERTIES[i] };
    }
}


void KeyboardState::draw(sf::RenderWindow& window)
{
    sf::RectangleShape rectangle;
    rectangle.setFillColor(sf::Color{100, 100, 100, 255});
    rectangle.setOutlineThickness(5);

    const sf::Color colors[6] = {
        sf::Color::Red,
        sf::Color::Green,
        sf::Color::Blue,
        sf::Color::Yellow,
        sf::Color::Magenta,
        sf::Color::Cyan
    };

    for (const auto& key : keys)
    {
        rectangle.setOutlineColor(colors[key.description->row]);
        const auto width = key.description->width * KEY_SIZE;
        const auto height = key.description->height * KEY_SIZE;
        rectangle.setSize(sf::Vector2f{width, height});
        const auto x = key.description->x * (KEY_SIZE + KEY_PADDING);
        const auto y = key.description->y * (KEY_SIZE + KEY_PADDING);
        rectangle.setPosition(x, y);
        window.draw(rectangle);
    }
}


}
