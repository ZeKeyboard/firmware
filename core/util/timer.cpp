#include "timer.h"


namespace core::util
{

void Timer::start(Device& device)
{
    running = true;
    remainingTime = duration;
    start_time = device.millis();
}

void Timer::stop()
{
    running = false;
}

void Timer::update(Device& device)
{
    if (running)
    {
        uint32_t current_time = device.millis();
        uint32_t elapsed = current_time - start_time;
        remainingTime = duration - elapsed;
        if (elapsed >= duration)
        {
            running = false;
            remainingTime = 0;
        }
    }
}

bool Timer::is_running() const
{
    return running;
}

bool Timer::is_finished() const
{
    return !running;
}

uint32_t Timer::remaining_time() const
{
    return remainingTime;
}

float Timer::progress() const
{
    return 1.0f - static_cast<float>(remainingTime) / static_cast<float>(duration);
}

}
