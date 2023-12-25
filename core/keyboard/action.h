#pragma once

#include <stdint.h>

namespace core::keyboard
{

struct KeyPress
{
    uint16_t key;
    uint16_t modifier;
    uint16_t media;
};

struct Action
{
    Action(uint16_t key);
    ~Action();

    Action(KeyPress* sequence, uint8_t sequence_length);

    KeyPress* sequence;
    uint8_t sequence_length;

    bool is_single_key() const;
    uint16_t get_single_key() const;
};

}

