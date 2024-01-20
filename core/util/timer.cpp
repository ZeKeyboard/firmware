#include "timer.h"


namespace core::util
{

void Timer::start(const Device& device)
{
    running = true;
    time_remaining = duration;
    start_time = device.milliseconds_since_start();
}

void Timer::update(const Device& device)
{
    if (running)
    {
        uint32_t current_time = device.milliseconds_since_start();
        uint32_t elapsed = current_time - start_time;
        time_remaining = duration - elapsed;
        if (elapsed >= duration)
        {
            running = false;
            time_remaining = 0;
        }
    }
}

bool Timer::is_finished() const
{
    return !running;
}

uint32_t Timer::remaining_time() const
{
    return time_remaining;
}

float Timer::progress() const
{
    return 1.0f - static_cast<float>(time_remaining) / static_cast<float>(duration);
}

}
