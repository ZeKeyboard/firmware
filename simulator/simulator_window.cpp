#include "simulator_window.h"

namespace simulator
{

SimulatorWindow::SimulatorWindow(Device& device) : device{device}
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

