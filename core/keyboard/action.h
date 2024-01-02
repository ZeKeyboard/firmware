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
    /**
     * Initialize an action with a single key.
     */
    Action(uint16_t key);

    /**
     * Initialize an action with a sequence of keys. Takes ownership of the sequence.
     */
    Action(KeyPress* sequence, uint8_t sequence_length);
    ~Action();

    KeyPress* sequence;
    uint8_t sequence_length;

    // TODO remove
    bool is_single_key() const;

    uint16_t get_single_key() const;
};

}

