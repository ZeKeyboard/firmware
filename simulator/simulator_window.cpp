#include "simulator_window.h"
#include "Window/Mouse.hpp"

namespace simulator
{

SimulatorWindow::SimulatorWindow(SimulatorDevice& device)
    : device{device}, keyboard_state{device}
{
    window.create(sf::VideoMode(1920, 1080), "Simulator");
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


void SimulatorWindow::draw()
{
    keyboard_state.draw(window);
}


bool SimulatorWindow::is_open() const
{
    return window.isOpen();
}

}

