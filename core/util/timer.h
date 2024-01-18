#pragma once

#include <stdint.h>
#include "../../device.h"

namespace core::util
{

// Note: the reason we cannot have Device& as a field in the Timer struct is because
// we would need to have a non-default constructor, which causes a problem for LEDState,
// which is in an array so it cannot be initialized using a non-default constructor.

struct Timer
{
    /**
     * Starts the timer, resetting the timer remaining to the duration.
     */
    void start(const Device& device);

    /**
     * Updates the internal state of the timer, run this before reading the timer state.
     */
    void update(const Device& device);

    /**
     * Whether the timer duration has elapsed.
     */
    bool is_finished() const;

    /**
     * The number of milliseconds remaining.
     */
    uint32_t remaining_time() const;

    /**
     * The percentage amount of time between the start and the duration.
     * 0 means just started, 1 means finished.
     */
    float progress() const;

    /**
     * The timer duration in milliseconds.
     */
    uint32_t duration;

private:
    uint32_t start_time = 0;
    uint32_t time_remaining = 0;
    bool running = false;
};

}
