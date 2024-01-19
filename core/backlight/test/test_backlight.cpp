#include <catch_amalgamated.hpp>
#include "../backlight.h"
#include "../../testutil/testdevice.h"
#include "../schemes/scheme.h"


class TestScheme : public core::backlight::schemes::Scheme
{
public:
    TestScheme(Device& device) : Scheme(device) { }

    void update(const core::keyboard::KeyboardScanResult&,
        core::backlight::LEDState led_states[common::constants::TOTAL_NUM_LEDS]) override
    {
        for (uint8_t i = 0; i < common::constants::TOTAL_NUM_LEDS; ++i)
        {
            led_states[i].color = colors[i];
            if (i == blink_index)
            {
                led_states[i].start_blink(device, 100);
                blink_index = -1;
            }
            else if (i == fade_index)
            {
                led_states[i].start_fade(device, fade_start_color, 100);
                fade_index = -1;
            }
        }
    }

    int blink_index = -1;
    int fade_index = -1;
    core::backlight::Color fade_start_color;

    void reset() override { }

    core::backlight::Color colors[common::constants::TOTAL_NUM_LEDS];
};


TEST_CASE("Test backlight", "[Backlight]")
{
    testutil::TestTimerLEDDevice device;
    TestScheme scheme{device};
    core::backlight::schemes::Scheme* schemes[] = { &scheme };

    SECTION("Test set colors")
    {
        core::backlight::Backlight backlight{device, schemes, 1};
        for (uint8_t i = 0; i < common::constants::TOTAL_NUM_LEDS; ++i)
        {
            float c = static_cast<float>(i) / static_cast<float>(common::constants::TOTAL_NUM_LEDS);
            scheme.colors[i] = core::backlight::Color{c, 1.0f - c, c};

        }
        backlight.update(core::keyboard::KeyboardScanResult{});
        for (uint8_t i = 0; i < common::constants::TOTAL_NUM_LEDS; ++i)
        {
            REQUIRE(device.leds_updated);
            auto c = static_cast<uint8_t>(255.0f * static_cast<float>(i) / static_cast<float>(common::constants::TOTAL_NUM_LEDS));
            auto not_c = static_cast<uint8_t>(255.0f * (1.0f - static_cast<float>(i) / static_cast<float>(common::constants::TOTAL_NUM_LEDS)));
            REQUIRE(device.led_colors_r[i] == c);
            REQUIRE(device.led_colors_g[i] == not_c);
            REQUIRE(device.led_colors_b[i] == c);
        }
    }

    SECTION("Test blink")
    {
        core::backlight::Backlight backlight{device, schemes, 1};

        scheme.colors[0] = core::backlight::Color{1.0f, 0.5f, 1.0f};
        scheme.blink_index = 0;

        device.current_millis = 0;
        backlight.update(core::keyboard::KeyboardScanResult{});
        REQUIRE(device.leds_updated);
        CHECK(device.led_colors_r[0] == 255);
        CHECK(device.led_colors_g[0] == 127);
        CHECK(device.led_colors_b[0] == 255);

        device.current_millis = 99;
        backlight.update(core::keyboard::KeyboardScanResult{});
        REQUIRE(device.leds_updated);
        CHECK(device.led_colors_r[0] == 255);
        CHECK(device.led_colors_g[0] == 127);
        CHECK(device.led_colors_b[0] == 255);

        device.current_millis = 150;
        backlight.update(core::keyboard::KeyboardScanResult{});
        REQUIRE(device.leds_updated);
        CHECK(device.led_colors_r[0] == 0);
        CHECK(device.led_colors_g[0] == 0);
        CHECK(device.led_colors_b[0] == 0);

        device.current_millis = 251;
        backlight.update(core::keyboard::KeyboardScanResult{});
        REQUIRE(device.leds_updated);
        CHECK(device.led_colors_r[0] == 255);
        CHECK(device.led_colors_g[0] == 127);
        CHECK(device.led_colors_b[0] == 255);
    }

    SECTION("Test fade")
    {
        core::backlight::Backlight backlight{device, schemes, 1};

        scheme.colors[0] = core::backlight::Color{1.0f, 0.0f, 0.0f};
        scheme.fade_start_color = core::backlight::Color{0.0f, 0.0f, 1.0f};
        scheme.fade_index = 0;

        device.current_millis = 0;
        backlight.update(core::keyboard::KeyboardScanResult{});
        REQUIRE(device.leds_updated);
        CHECK(device.led_colors_r[0] == 0);
        CHECK(device.led_colors_g[0] == 0);
        CHECK(device.led_colors_b[0] == 255);

        device.current_millis = 50;
        backlight.update(core::keyboard::KeyboardScanResult{});
        REQUIRE(device.leds_updated);
        CHECK(device.led_colors_r[0] == 127);
        CHECK(device.led_colors_g[0] == 0);
        CHECK(device.led_colors_b[0] == 127);

        device.current_millis = 100;
        backlight.update(core::keyboard::KeyboardScanResult{});
        REQUIRE(device.leds_updated);
        CHECK(device.led_colors_r[0] == 255);
        CHECK(device.led_colors_g[0] == 0);
        CHECK(device.led_colors_b[0] == 0);
    }
}
