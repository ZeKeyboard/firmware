#include "keyboard_state.h"
#include "Graphics/RectangleShape.hpp"
#include <Graphics/RenderWindow.hpp>
#include <Window/Mouse.hpp>

#include "keycodes.h"


namespace simulator
{

const int KEY_SIZE = 60;
const int KEY_PADDING = 40;

const int OFFSET_X = 100;
const int OFFSET_Y = 100;

KeyboardState::KeyboardState(SimulatorDevice& device, const core::keyboard::KeyMap& key_map, const sf::Font& font) : device{device}, font{font}, keymap{key_map}
{
    for (unsigned i = 0; i < common::constants::TOTAL_NUM_KEYS; ++i)
    {
        keys[i] = { false, false, &common::constants::KEY_PROPERTIES[i] };
    }
}


void KeyboardState::handle_input(sf::RenderWindow& window)
{
    for (auto& key : keys)
    {
        key.hovered = false;
    }

    const auto mouse_position = sf::Mouse::getPosition(window);
    const auto mouse_x = mouse_position.x;
    const auto mouse_y = mouse_position.y;

    for (auto& key : keys)
    {
        const auto key_x = key.description->x * (KEY_SIZE + KEY_PADDING) + OFFSET_X;
        const auto key_y = key.description->y * (KEY_SIZE + KEY_PADDING) + OFFSET_Y;
        const auto key_width = key.description->width * KEY_SIZE;
        const auto key_height = key.description->height * KEY_SIZE;

        key.hovered = mouse_x >= key_x && mouse_x <= key_x + key_width &&
            mouse_y >= key_y && mouse_y <= key_y + key_height;
    }

    for (auto& key : keys)
    {
        key.pressed = key.hovered && sf::Mouse::isButtonPressed(sf::Mouse::Left);
        device.set_pressed_row_and_col(key.description->row, key.description->col, key.pressed);
    }
}


void KeyboardState::draw_row_and_col_state(
    sf::RenderWindow& window,
    const int row,
    const int col,
    const float x,
    const float y)
{
    sf::RectangleShape row_rect;
    row_rect.setFillColor(sf::Color{255, 255, 255, 255});
    row_rect.setSize(sf::Vector2f{KEY_SIZE, 5});
    row_rect.setPosition(x, y + static_cast<float>(KEY_SIZE) / 2);
    const auto should_visualize_row = !device.row_state[row];
    if (should_visualize_row)
    {
        window.draw(row_rect);
    }

    sf::RectangleShape col_rect;
    col_rect.setFillColor(sf::Color{255, 100, 255, 255});
    col_rect.setSize(sf::Vector2f{5, KEY_SIZE});
    col_rect.setPosition(x + static_cast<float>(KEY_SIZE) / 2, y);
    const auto should_visualize_col = device.last_read_col == col;
    if (should_visualize_col)
    {
        window.draw(col_rect);
    }

    const auto action = keymap.actions[row][col];
    if (action != nullptr && action->is_single_key())
    {
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::White);
        const auto code = action->get_single_key();
        if (KEY_CODES.contains(code))
        {
            text.setString(KEY_CODES.at(code));
        }
        else
        {
            text.setString(std::to_string(code));
        }
        text.setPosition(x + KEY_SIZE/4.0, y + KEY_SIZE/4.0);
        window.draw(text);
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
        const auto x = key.description->x * (KEY_SIZE + KEY_PADDING) + OFFSET_X;
        const auto y = key.description->y * (KEY_SIZE + KEY_PADDING) + OFFSET_Y;
        rectangle.setPosition(x, y);
        window.draw(rectangle);
        draw_row_and_col_state(window, key.description->row, key.description->col, x, y);
    }
}

}
