#include <catch_amalgamated.hpp>
#include "../../testutil/testdevice.h"
#include "../../testutil/testutilities.h"
#include "../timer.h"


TEST_CASE("Test timer", "[Timer]")
{
    testutil::TestTimerLEDDevice device;

    core::util::Timer timer;
    timer.duration = 100;

    // the timer should be able to restart without reinitialization
    for (int i = 0; i < 2; ++i)
    {
        const uint32_t time_offset = i * 200;
        device.current_millis = 0 + time_offset;
        timer.start(device);

        timer.update(device);
        // no time has passed yet
        CHECK(timer.remaining_time() == 100);
        CHECK(testutil::float_equals(timer.progress(), 0.0f));
        CHECK(!timer.is_finished());

        device.current_millis = 50 + time_offset;

        timer.update(device);
        // 50 milliseconds have passed
        CHECK(timer.remaining_time() == 50);
        CHECK(testutil::float_equals(timer.progress(), 0.5f));
        CHECK(!timer.is_finished());

        device.current_millis = 99 + time_offset;

        timer.update(device);
        CHECK(timer.remaining_time() == 1);
        CHECK(testutil::float_equals(timer.progress(), 0.99f));
        CHECK(!timer.is_finished());

        device.current_millis = 101 + time_offset;

        timer.update(device);
        CHECK(timer.remaining_time() == 0);
        CHECK(testutil::float_equals(timer.progress(), 1.0f));
        CHECK(timer.is_finished());
    }
}
