#include "../keymap.h"
#include <catch_amalgamated.hpp>


const uint16_t VALID_DATA[]
{
    3,      // num keys
    22664,  // checksum

    0,  // row 0
    0,  // col 0
    // action 1
    1,                // sequence length
    (4    | 0xF000),  // key A
    (0    | 0xE000),  // no modifier
    (0    | 0xE400),  // no media

    1,  // row 1
    3,  // col 3
    // action 2
    2,                // sequence length
    (6    | 0xF000),  // key C
    (0x01 | 0xE000),  // ctrl
    (0    | 0xE400),  // no media
    (25   | 0xF000),  // key V
    (0x01 | 0xE000),  // ctrl
    (0    | 0xE400),  // no media

    2,  // row 2
    3,  // col 3
    // action 3
    6,                // sequence length
    (0    | 0xF000),  // no key
    (0    | 0xE000),  // no modifier
    (0xCD | 0xE400),  // Play / Pause
    (14   | 0xF000),  // key K
    (0    | 0xE000),  // no modifier
    (0    | 0xE400),  // no media
    (8    | 0xF000),  // key E
    (0    | 0xE000),  // ctrl
    (0    | 0xE400),  // no media
    (5    | 0xF000),  // key B
    (0    | 0xE000),  // ctrl
    (0    | 0xE400),  // no media
    (4    | 0xF000),  // key A
    (0    | 0xE000),  // ctrl
    (0    | 0xE400),  // no media
    (5    | 0xF000),  // key B
    (0    | 0xE000),  // ctrl
    (0    | 0xE400),  // no media
};


TEST_CASE("Test keymap load", "[KeyMap]")
{

    const uint16_t invalid_checksum[]
    {
        3,   // num keys
        22,  // incorrect checksum

        0,  // row 0
        0,  // col 0
        // action 1
        1,                // sequence length
        (4    | 0xF000),  // key A
        (0    | 0xE000),  // no modifier
        (0    | 0xE400),  // no media

        1,  // row 1
        3,  // col 3
        // action 2
        2,                // sequence length
        (6    | 0xF000),  // key C
        (0x01 | 0xE000),  // ctrl
        (0    | 0xE400),  // no media
        (25   | 0xF000),  // key V
        (0x01 | 0xE000),  // ctrl
        (0    | 0xE400),  // no media

        2,  // row 2
        3,  // col 3
        // action 3
        6,                // sequence length
        (0    | 0xF000),  // no key
        (0    | 0xE000),  // no modifier
        (0    | 0xE400),  // no media
        (14   | 0xF000),  // key K
        (0    | 0xE000),  // no modifier
        (0    | 0xE400),  // no media
        (8    | 0xF000),  // key E
        (0    | 0xE000),  // ctrl
        (0    | 0xE400),  // no media
        (5    | 0xF000),  // key B
        (0    | 0xE000),  // ctrl
        (0    | 0xE400),  // no media
        (4    | 0xF000),  // key A
        (0    | 0xE000),  // ctrl
        (0    | 0xE400),  // no media
        (5    | 0xF000),  // key B
        (0    | 0xE000),  // ctrl
        (0    | 0xE400),  // no media
    };

    const uint16_t invalid_sequence_lengths[]
    {
        3,      // num keys
        22664,  // checksum

        0,  // row 0
        0,  // col 0
        // action 1
        2,                // INVALID sequence length
        (4    | 0xF000),  // key A
        (0    | 0xE000),  // no modifier
        (0    | 0xE400),  // no media

        1,  // row 1
        3,  // col 3
        // action 2
        1,                // INVALID sequence length
        (6    | 0xF000),  // key C
        (0x01 | 0xE000),  // ctrl
        (0    | 0xE400),  // no media
        (25   | 0xF000),  // key V
        (0x01 | 0xE000),  // ctrl
        (0    | 0xE400),  // no media

        2,  // row 2
        3,  // col 3
        // action 3
        6,                // sequence length
        (0    | 0xF000),  // no key
        (0    | 0xE000),  // no modifier
        (0xCD | 0xE400),  // Play / Pause
        (14   | 0xF000),  // key K
        (0    | 0xE000),  // no modifier
        (0    | 0xE400),  // no media
        (8    | 0xF000),  // key E
        (0    | 0xE000),  // ctrl
        (0    | 0xE400),  // no media
        (5    | 0xF000),  // key B
        (0    | 0xE000),  // ctrl
        (0    | 0xE400),  // no media
        (4    | 0xF000),  // key A
        (0    | 0xE000),  // ctrl
        (0    | 0xE400),  // no media
        (5    | 0xF000),  // key B
        (0    | 0xE000),  // ctrl
        (0    | 0xE400),  // no media
    };

    const uint16_t invalid_keycodes[]
    {
        3,      // num keys
        9354,  // checksum

        0,  // row 0
        0,  // col 0
        // action 1
        1,                // sequence length
        (1    | 0xF000),  // INVALID key
        (0    | 0xE000),  // no modifier
        (0    | 0xE400),  // no media

        1,  // row 1
        3,  // col 3
        // action 2
        2,                // sequence length
        (6    | 0xF000),  // key C
        (0x01 | 0xA000),  // INVALID modifier
        (0    | 0xE400),  // no media
        (25   | 0xF000),  // key V
        (0x01 | 0xE000),  // ctrl
        (5    | 0xF000),  // invalid media

        2,  // row 2
        3,  // col 3
        // action 3
        6,                // sequence length
        (0    | 0xF000),  // no key
        (0    | 0xE000),  // no modifier
        (0xCD | 0xE400),  // Play / Pause
        (14   | 0xF000),  // key K
        (0    | 0xE000),  // no modifier
        (0    | 0xE400),  // no media
        (8    | 0xF000),  // key E
        (0    | 0xE000),  // ctrl
        (0    | 0xE400),  // no media
        (5    | 0xF000),  // key B
        (0    | 0xE000),  // ctrl
        (0    | 0xE400),  // no media
        (4    | 0xF000),  // key A
        (0    | 0xE000),  // ctrl
        (0    | 0xE400),  // no media
        (5    | 0xF000),  // key B
        (0    | 0xE000),  // ctrl
        (0    | 0xE400),  // no media
    };

    SECTION("Test valid")
    {
        uint16_t rows[] = {0, 1, 2};
        uint16_t cols[] = {0, 3, 3};

        core::keyboard::KeyMap keymap;
        const auto success = keymap.load(VALID_DATA, sizeof(VALID_DATA) / sizeof(VALID_DATA[0]));
        REQUIRE(success);

        for (unsigned r = 0; r < common::constants::NUM_ROWS; ++r)
        {
            for (unsigned c = 0; c < common::constants::NUM_COLS; ++c)
            {
                bool shouldNotBeNull = false;
                for (int i = 0; i < 3; ++i)
                {
                    if (rows[i] == r && cols[i] == c)
                    {
                        shouldNotBeNull = true;
                        break;
                    }
                }
                if (shouldNotBeNull)
                {
                    continue;
                }

                // assert that most are null
                const auto action = keymap.get_action(r, c);
                CHECK((action == nullptr));
            }
        }

        const auto action1 = keymap.get_action(0, 0);
        CHECK(action1 != nullptr);
        CHECK(action1->sequence_length == 1);
        CHECK(action1->sequence[0].key == (4 | 0xF000));
        CHECK(action1->sequence[0].modifier == 0xE000);
        CHECK(action1->sequence[0].media == 0xE400);

        const auto action2 = keymap.get_action(1, 3);
        CHECK(action2 != nullptr);
        CHECK(action2->sequence_length == 2);
        CHECK(action2->sequence[0].key == (6 | 0xF000));
        CHECK(action2->sequence[0].modifier == (0x01 | 0xE000));
        CHECK(action2->sequence[0].media == 0xE400);
        CHECK(action2->sequence[1].key == (25 | 0xF000));
        CHECK(action2->sequence[1].modifier == (0x01 | 0xE000));
        CHECK(action2->sequence[1].media == 0xE400);

        const auto action3 = keymap.get_action(2, 3);
        CHECK(action3 != nullptr);
        CHECK(action3->sequence_length == 6);
        CHECK(action3->sequence[0].key == 0xF000);
        CHECK(action3->sequence[0].modifier == 0xE000);
        CHECK(action3->sequence[0].media == (0xCD | 0xE400));
        CHECK(action3->sequence[1].key == (14 | 0xF000));
        CHECK(action3->sequence[1].modifier == 0xE000);
        CHECK(action3->sequence[1].media == 0xE400);
        CHECK(action3->sequence[2].key == (8 | 0xF000));
        CHECK(action3->sequence[2].modifier == 0xE000);
        CHECK(action3->sequence[2].media == 0xE400);
        CHECK(action3->sequence[3].key == (5 | 0xF000));
        CHECK(action3->sequence[3].modifier == 0xE000);
        CHECK(action3->sequence[3].media == 0xE400);
        CHECK(action3->sequence[4].key == (4 | 0xF000));
        CHECK(action3->sequence[4].modifier == 0xE000);
        CHECK(action3->sequence[4].media == 0xE400);
        CHECK(action3->sequence[5].key == (5 | 0xF000));
        CHECK(action3->sequence[5].modifier == 0xE000);
        CHECK(action3->sequence[5].media == 0xE400);
    }

    SECTION("Test invalid checksum")
    {
        core::keyboard::KeyMap keymap;
        const auto success = keymap.load(invalid_checksum,
            sizeof(invalid_checksum) / sizeof(invalid_checksum[0]));
        REQUIRE(!success);
    }

    SECTION("Test invalid sequence lengths")
    {
        core::keyboard::KeyMap keymap;
        const auto success = keymap.load(invalid_sequence_lengths,
            sizeof(invalid_sequence_lengths) / sizeof(invalid_sequence_lengths[0]));
        REQUIRE(!success);
    }
    SECTION("Test invalid keycodes")
    {
        core::keyboard::KeyMap keymap;
        const auto success = keymap.load(invalid_keycodes,
            sizeof(invalid_keycodes) / sizeof(invalid_keycodes[0]));
        REQUIRE(!success);
    }
}

TEST_CASE("Test translate scan result", "[KeyMap]")
{
    core::keyboard::KeyMap keymap;
    const auto success = keymap.load(VALID_DATA, sizeof(VALID_DATA) / sizeof(VALID_DATA[0]));
    REQUIRE(success);

    const common::KeyDescription descriptions[]
    {
        {0, 0, 0, 0, 1, 1, 0},  // 0
        {1, 3, 1, 3, 1, 1, 0},  // 1
        {2, 3, 2, 3, 1, 1, 0},  // 2
    };

    SECTION("Test nothing pressed")
    {
        core::keyboard::KeyQueue queue;
        core::keyboard::KeyboardScanResult scan_result;
        scan_result.num_pressed = 0;

        keymap.translate_keyboard_scan_result(scan_result, queue);

        CHECK(queue.size() == 0);
    }

    SECTION("Test single key")
    {
        core::keyboard::KeyQueue queue;
        core::keyboard::KeyboardScanResult scan_result;
        scan_result.num_pressed = 1;
        scan_result.pressed[0] = &descriptions[0];

        keymap.translate_keyboard_scan_result(scan_result, queue);

        CHECK(queue.size() == 1);
        CHECK(queue.front().num_keys == 1);
        CHECK(queue.front().keys[0] == (4 | 0xF000));
        CHECK(queue.front().modifier == 0xE000);
        CHECK(queue.front().media == 0xE400);
    }

    SECTION("Test multiple keys pressed")
    {
        const uint16_t data[]
        {
            7,      // num keys
            61144,  // checksum

            0,  // row 0
            0,  // col 0
            1,                // sequence length
            (4    | 0xF000),  // key A
            (0    | 0xE000),  // no modifier
            (0    | 0xE400),  // no media

            0,  // row 0
            1,  // col 1
            1,                // sequence length
            (5    | 0xF000),  // key B
            (0    | 0xE000),  // no modifier
            (0    | 0xE400),  // no media

            0,  // row 0
            2,  // col 2
            1,                // sequence length
            (6    | 0xF000),  // key C
            (2    | 0xE000),  // shift
            (0    | 0xE400),  // no media

            0,  // row 0
            3,  // col 3
            1,                // sequence length
            (7    | 0xF000),  // key D
            (1    | 0xE000),  // ctrl
            (0    | 0xE400),  // no media

            0,  // row 0
            4,  // col 4
            1,                // sequence length
            (8    | 0xF000),  // key E
            (0    | 0xE000),  // no modifier
            (0    | 0xE400),  // no media

            0,  // row 0
            5,  // col 5
            1,                // sequence length
            (9    | 0xF000),  // key F
            (0    | 0xE000),  // no modifier
            (0    | 0xE400),  // no media

            0,  // row 0
            6,  // col 6
            1,                // sequence length
            (10   | 0xF000),  // key G
            (0    | 0xE000),  // no modifier
            (0    | 0xE400),  // no media
        };

        const common::KeyDescription descriptions[]
        {
            {0, 0, 0, 0, 1, 1, 0},  // 0
            {0, 1, 1, 3, 1, 1, 0},  // 1
            {0, 2, 2, 3, 1, 1, 0},  // 2
            {0, 3, 2, 3, 1, 1, 0},  // 3
            {0, 4, 2, 3, 1, 1, 0},  // 4
            {0, 5, 2, 3, 1, 1, 0},  // 5
            {0, 6, 2, 3, 1, 1, 0},  // 6
        };

        core::keyboard::KeyMap keymap;
        const auto success = keymap.load(data, sizeof(data) / sizeof(data[0]));
        REQUIRE(success);

        core::keyboard::KeyQueue queue;
        core::keyboard::KeyboardScanResult scan_result;
        scan_result.num_pressed = 7;

        for (int i = 0; i < 7; ++i)
        {
            scan_result.pressed[i] = &descriptions[i];
        }

        keymap.translate_keyboard_scan_result(scan_result, queue);

        CHECK(queue.size() == 1);
        CHECK(queue.front().num_keys == 6);
        CHECK(queue.front().keys[0] == (10 | 0xF000));
        CHECK(queue.front().keys[1] == (9  | 0xF000));
        CHECK(queue.front().keys[2] == (8  | 0xF000));
        CHECK(queue.front().keys[3] == (7  | 0xF000));
        CHECK(queue.front().keys[4] == (6  | 0xF000));
        CHECK(queue.front().keys[5] == (5  | 0xF000));
        CHECK(queue.front().modifier == (0x03 | 0xE000));
        CHECK(queue.front().media == 0xE400);
    }

    SECTION("Test sequence")
    {
        core::keyboard::KeyQueue queue;
        core::keyboard::KeyboardScanResult scan_result;
        scan_result.num_pressed = 1;
        scan_result.pressed[0] = &descriptions[1];

        keymap.translate_keyboard_scan_result(scan_result, queue);

        CHECK(queue.size() == 2);
        CHECK(queue.front().num_keys == 1);
        CHECK(queue.front().keys[0] == (6 | 0xF000));
        CHECK(queue.front().modifier == (0x01 | 0xE000));
        CHECK(queue.front().media == 0xE400);
        queue.pop();

        CHECK(queue.front().num_keys == 1);
        CHECK(queue.front().keys[0] == (25 | 0xF000));
        CHECK(queue.front().modifier == (0x01 | 0xE000));
        CHECK(queue.front().media == 0xE400);
    }
}
