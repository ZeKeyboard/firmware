#include "simulator_window.h"
#include "Graphics/Font.hpp"
#include "Graphics/Text.hpp"
#include "keycodes.h"
#include <sstream>

namespace simulator
{

const int QUEUE_TEXT_POS_X = 10;
const int QUEUE_TEXT_POS_Y = 900;

const int SENT_KEYS_TEXT_POS_X = 500;
const int SENT_KEYS_TEXT_POS_Y = 900;

SimulatorWindow::SimulatorWindow(SimulatorDevice& device, core::Firmware& firmware)
    : device{device}, firmware{firmware}, keyboard_state{device, firmware.keymap, font}
{
    window.create(sf::VideoMode(1920, 1080), "Simulator");
    font.loadFromFile("../resources/arial.ttf");
}

void SimulatorWindow::update()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
            exit(0);
        }
    }

    window.clear();
    keyboard_state.handle_input(window);
    draw();
    window.display();
}


void SimulatorWindow::draw_firmware()
{
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::White);

    if (firmware.key_queue.empty())
    {
        text.setString("[]");
    }
    else
    {
        std::stringstream ss;
        for (int i = 0; i < firmware.key_queue.size(); ++i)
        {
            const auto key_report = firmware.key_queue.peek_at(i);
            ss << "[";
            for (int i = 0; i < key_report.num_keys; ++i)
            {
                const auto key = key_report.keys[i];
                if (KEY_CODES.contains(key))
                {
                    ss << KEY_CODES.at(key) << " ";
                }
                else
                {
                    ss << (int)key << " ";
                }
            }
            ss << "] ";
            ss << "Modifier: " << (int)key_report.modifier << " Media: " << (int)key_report.media;
            ss << "\n";
        }

        text.setString(ss.str());
    }
    text.setPosition(QUEUE_TEXT_POS_X, QUEUE_TEXT_POS_Y);
    window.draw(text);
}


void SimulatorWindow::draw()
{
    keyboard_state.draw(window);
    draw_firmware();
    draw_sent_keys();
}

void SimulatorWindow::draw_sent_keys()
{
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::Magenta);
    text.setPosition(SENT_KEYS_TEXT_POS_X, SENT_KEYS_TEXT_POS_Y);
    std::stringstream ss;
    ss << "Sent keys: ";
    for (int i = 0; i < common::constants::MAX_KEYREPORT_KEYS; ++i)
    {
        const auto code = device.current_keys[i];
        const auto full_code = 0xF000 | code;
        if (KEY_CODES.contains(full_code))
        {
            ss << KEY_CODES.at(full_code) << " ";
        }
        else
        {
            ss << (int)code << " ";
        }
    }
    ss << "\nModifier: " << (int)device.current_modifier << ", Media: " << (int)device.current_media;
    text.setString(ss.str());
    window.draw(text);
}


bool SimulatorWindow::is_open() const
{
    return window.isOpen();
}

}

