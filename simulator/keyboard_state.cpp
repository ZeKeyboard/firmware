#include "keyboard_state.h"


namespace simulator
{

const int KEY_SIZE = 80;
const int KEY_PADDING = 20;

KeyboardState::KeyboardState()
{
    for (unsigned i = 0; i < common::constants::TOTAL_NUM_KEYS; ++i)
    {
        keys[i] = { false, false, &common::constants::KEY_PROPERTIES[i] };
    }
}


void KeyboardState::handle_input()
{
    for (auto& key : keys)
    {
        key.hovered = false;
    }

    const auto mouse_position = sf::Mouse::getPosition();
    const auto mouse_x = mouse_position.x;
    const auto mouse_y = mouse_position.y;

    for (auto& key : keys)
    {
        const auto key_x = key.description->x * (KEY_SIZE + KEY_PADDING);
        const auto key_y = key.description->y * (KEY_SIZE + KEY_PADDING) + KEY_SIZE;
        const auto key_width = key.description->width * (KEY_SIZE + KEY_PADDING);
        const auto key_height = key.description->height * (KEY_SIZE + KEY_PADDING);

        if (mouse_x >= key_x && mouse_x <= key_x + key_width &&
            mouse_y >= key_y && mouse_y <= key_y + key_height)
        {
            key.hovered = true;
        }
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        for (auto& key : keys)
        {
            if (key.hovered)
            {
                key.pressed = true;
            }
        }
    }
    else
    {
        for (auto& key : keys)
        {
            key.pressed = false;
        }
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
        if (key.pressed)
        {
            rectangle.setFillColor(sf::Color{0, 0, 0, 255});
        }
        else if (key.hovered)
        {
            rectangle.setFillColor(sf::Color{150, 150, 150, 255});
        }
        else
        {
            rectangle.setFillColor(sf::Color{100, 100, 100, 255});
        }

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
