#pragma once

#include <stdint.h>
#include "../../device.h"

namespace core::util
{

struct Timer
{
    void start(Device& device);
    void stop();
    void update(Device& device);
    bool is_running() const;
    bool is_finished() const;
    uint32_t remaining_time() const;
    float progress() const;
    uint32_t duration;

private:
    uint32_t start_time;
    uint32_t remainingTime;
    bool running = false;
};

}
