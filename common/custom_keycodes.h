#pragma once

#include <stdint.h>

namespace common::constants
{

const uint16_t LAYER_HOLD_MODIFIER = 0xC000;
const uint16_t LAYER_TOGGLE_MODIFIER = 0xB000;

const uint16_t LAYER_HOLD_0 = (0 | LAYER_HOLD_MODIFIER);
const uint16_t LAYER_HOLD_1 = (1 | LAYER_HOLD_MODIFIER);
const uint16_t LAYER_HOLD_2 = (2 | LAYER_HOLD_MODIFIER);

const uint16_t LAYER_TOGGLE_0 = (0 | LAYER_TOGGLE_MODIFIER);
const uint16_t LAYER_TOGGLE_1 = (1 | LAYER_TOGGLE_MODIFIER);
const uint16_t LAYER_TOGGLE_2 = (2 | LAYER_TOGGLE_MODIFIER);

}
