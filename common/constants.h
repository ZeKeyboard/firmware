#pragma once

#include "../generated/hardware_layout.h"
#include "custom_keycodes.h"


namespace common::constants
{

const int MAX_JUST_PRESSED_KEYS = TOTAL_NUM_KEYS;

const int MAX_QUEUED_KEY_EVENTS = 20;

const int MAX_KEYREPORT_KEYS = 6;

const int MAX_NUM_LAYERS = 3;

const uint8_t COL_PINS[] =
{
    35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 12, 11, 10, 9, 8, 7, 6
};


const uint8_t ROW_PINS[] =
{
    5, 4, 3, 2, 1, 0
};

const uint16_t CHECKSUM_PERIOD = 65500;

}
