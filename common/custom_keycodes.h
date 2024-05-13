#pragma once

#include <stdint.h>

namespace common::constants
{

const uint16_t LAYER_HOLD_MODIFIER = 0xC000;
const uint16_t LAYER_TOGGLE_MODIFIER = 0xB000;
const uint16_t MOUSE_BASE_CODE = 0xA000;
const uint16_t CONTROL_BASE_CODE = 0xD000;

const uint16_t LAYER_HOLD_1 = (1 | LAYER_HOLD_MODIFIER);
const uint16_t LAYER_HOLD_2 = (2 | LAYER_HOLD_MODIFIER);

const uint16_t LAYER_TOGGLE_1 = (1 | LAYER_TOGGLE_MODIFIER);
const uint16_t LAYER_TOGGLE_2 = (2 | LAYER_TOGGLE_MODIFIER);

const uint16_t MOUSE_LEFT_CLICK =       (0 | MOUSE_BASE_CODE);
const uint16_t MOUSE_RIGHT_CLICK =      (1 | MOUSE_BASE_CODE);
const uint16_t MOUSE_MIDDLE_CLICK =     (2 | MOUSE_BASE_CODE);
const uint16_t MOUSE_SCROLL_UP =        (3 | MOUSE_BASE_CODE);
const uint16_t MOUSE_SCROLL_DOWN =      (4 | MOUSE_BASE_CODE);
const uint16_t MOUSE_MOVE_LEFT =        (5 | MOUSE_BASE_CODE);
const uint16_t MOUSE_MOVE_RIGHT =       (6 | MOUSE_BASE_CODE);
const uint16_t MOUSE_MOVE_UP =          (7 | MOUSE_BASE_CODE);
const uint16_t MOUSE_MOVE_DOWN =        (8 | MOUSE_BASE_CODE);
const uint16_t MOUSE_MOVE_ACCELERATE =  (9 | MOUSE_BASE_CODE);
const uint16_t MAX_MOUSE_CODE = 9;

const uint16_t CONTROL_BRIGHTNESS_INC =     (0 | CONTROL_BASE_CODE);
const uint16_t CONTROL_BRIGHTNESS_DEC =     (1 | CONTROL_BASE_CODE);
const uint16_t CONTROL_CONFIG_MODE_TOGGLE = (2 | CONTROL_BASE_CODE);
const uint16_t MAX_CONTROL_CODE = 2;

}
