#include "../keyscan.h"
#include <catch_amalgamated.hpp>


TEST_CASE("Test KeyboardScanResult", "[KeyboardScanResult]")
{
    common::KeyDescription test_keys[common::constants::TOTAL_NUM_KEYS];
    for (int i = 0; i < common::constants::TOTAL_NUM_KEYS; ++i)
    {
        // the properties don't really matter for this test
        test_keys[i].row = i / common::constants::NUM_COLS;
        test_keys[i].col = i % common::constants::NUM_COLS;
    }


    SECTION("try_add_just_pressed")
    {
        core::keyboard::KeyboardScanResult result;
        for (int i = 0; i < common::constants::MAX_JUST_PRESSED_KEYS; ++i)
        {
            result.try_add_pressed_key(&test_keys[i]);
            REQUIRE(result.num_just_pressed == i + 1);
            REQUIRE(result.just_pressed[i] == &test_keys[i]);
        }

        result.try_add_pressed_key(&test_keys[0]);
        const auto last_index = common::constants::MAX_JUST_PRESSED_KEYS - 1;
        REQUIRE(result.just_pressed[last_index] == &test_keys[last_index]);
    }

    SECTION("Update and reset")
    {
        core::keyboard::KeyboardScanResult result;
        result.reset_just_pressed();
        result.try_add_pressed_key(&test_keys[1]);

        // after update, the just pressed key should be moved to pressed
        result.update();
        REQUIRE(result.num_just_released == 0);
        REQUIRE(result.num_pressed == 1);
        REQUIRE(result.pressed[0] == &test_keys[1]);

        // since we are still pressing the same key, the just released should still be empty, and the key should not be in just_pressed
        result.reset_just_pressed();
        result.try_add_pressed_key(&test_keys[1]);
        result.update();
        REQUIRE(result.num_just_pressed == 0);
        REQUIRE(result.num_pressed == 1);
        REQUIRE(result.pressed[0] == &test_keys[1]);
        REQUIRE(result.num_just_released == 0);

        result.reset_just_pressed();
        result.try_add_pressed_key(&test_keys[2]);
        result.try_add_pressed_key(&test_keys[3]);
        result.update();

        REQUIRE(result.num_just_pressed == 2);
        REQUIRE(result.just_pressed[0] == &test_keys[2]);
        REQUIRE(result.just_pressed[1] == &test_keys[3]);
        REQUIRE(result.num_pressed == 2);
        REQUIRE(result.pressed[0] == &test_keys[2]);
        REQUIRE(result.pressed[1] == &test_keys[3]);
        REQUIRE(result.num_just_released == 1);
        REQUIRE(result.just_released[0] == &test_keys[1]);
    }

    SECTION("Update and reset many keys")
    {
        core::keyboard::KeyboardScanResult result;
        for (int i = 0; i < common::constants::MAX_JUST_PRESSED_KEYS; ++i)
        {
            result.try_add_pressed_key(&test_keys[i]);
        }

        // just_pressed is full, this should not do anything
        result.try_add_pressed_key(&test_keys[0]);

        result.update();
        REQUIRE(result.num_just_pressed == common::constants::MAX_JUST_PRESSED_KEYS);
        REQUIRE(result.num_pressed == common::constants::MAX_JUST_PRESSED_KEYS);
        for (int i = 0; i < common::constants::MAX_JUST_PRESSED_KEYS; ++i)
        {
            REQUIRE(result.just_pressed[i] == &test_keys[i]);
            REQUIRE(result.pressed[i] == &test_keys[i]);
        }
        REQUIRE(result.num_just_released == 0);

        result.reset_just_pressed();
        result.try_add_pressed_key(&test_keys[0]);
        result.update();
        REQUIRE(result.num_just_pressed == 0);
        REQUIRE(result.num_pressed == 1);
        REQUIRE(result.pressed[0] == &test_keys[0]);
        REQUIRE(result.num_just_released == common::constants::MAX_JUST_PRESSED_KEYS - 1);
        for (int i = 0; i < common::constants::MAX_JUST_PRESSED_KEYS - 1; ++i)
        {
            REQUIRE(result.just_released[i] == &test_keys[i + 1]);
        }
    }
}
