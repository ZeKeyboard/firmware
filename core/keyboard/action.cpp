#include "action.h"
#include "keyutils.h"

namespace core::keyboard
{

Action::Action(uint16_t key)
{
    sequence = new KeyPress[1];
    sequence[0].key = util::key_is_standard_key(key) ? key : 0;
    sequence[0].modifier = util::key_is_modifier(key) ? key : 0;
    sequence[0].media = util::key_is_media(key) ? key : 0;
    sequence_length = 1;
}

Action::~Action()
{
    delete[] sequence;
}

Action::Action(KeyPress* sequence, uint8_t sequence_length)
{
    this->sequence = sequence;
    this->sequence_length = sequence_length;
}

bool Action::is_single_key() const
{
    return sequence_length == 1;
}

uint16_t Action::get_single_key() const
{
    return sequence[0].key | sequence[0].modifier | sequence[0].media;
}

}
