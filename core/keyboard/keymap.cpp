#include "keymap.h"
#include "keyutils.h"


namespace core::keyboard
{

void KeyReport::add_key(uint16_t key)
{
    if (util::key_is_valid_standard_key(key))
    {
        if (num_keys < common::constants::MAX_KEYREPORT_KEYS)
        {
            keys[num_keys++] = key;
        }
    }
    else if (util::key_is_valid_modifier(key))
    {
        modifier |= key;
    }
    else if (util::key_is_media(key) && !util::key_is_blank(key))
    {
        media = key;
    }
}


bool KeyMap::check_checksum(const uint16_t* data, int size) const
{
    if (size < 2)
    {
        return false;
    }
    uint16_t checksum = 0;
    for (int i = 2; i < size; i++)
    {
        checksum = (checksum + data[i]) % common::constants::CHECKSUM_PERIOD;
    }
    return checksum == data[1];
}


bool KeyMap::check_sequence_lengths(const uint16_t* data, int size) const
{
    if (size < 2)
    {
        return false;
    }
    int expected_num_keys = data[0];
    int total_sequence_length = 0;
    int total_number_of_keys = 0;
    for (int i = 2; i < size;)
    {
        i += 2;

        const uint16_t sequence_length = data[i++];
        if (sequence_length == 0)
        {
            return false;
        }
        i += sequence_length * 3;
        total_number_of_keys++;

        total_sequence_length += sequence_length;
    }

    if (total_number_of_keys != expected_num_keys)
    {
        return false;
    }

    const int expected_size = 2 + total_number_of_keys * 3 + total_sequence_length * 3;

    if (size != expected_size)
    {
        return false;
    }
    return true;
}


void KeyMap::load_default()
{
    for (int row = 0; row < common::constants::NUM_ROWS; row++)
    {
        for (int col = 0; col < common::constants::NUM_COLS; col++)
        {
            const auto key_props = common::constants::KEY_PROPERTIES_BY_ROW_COL[row][col];
            if (key_props != nullptr)
            {
                actions[row][col] = new Action(key_props->default_key);
            }
            else
            {
                actions[row][col] = nullptr;
            }
        }
    }
}


void KeyMap::translate_keyboard_scan_result(const KeyboardScanResult& scan_result, KeyQueue& key_queue) const
{
    /*
     * This function implements the following logic:
     * For each key in the scan result:
     * If the keys are single keys (not part of a sequence),
     * they should all be sent together in a single report. This is because the user
     * might be holding down several keys together.
     * If the keys are part of a sequence, they should be sent in separate report, all queued up. This is because they need to be sent separately for the computer to intepret them as separate keypresses.
     */

    KeyReport single_key_report;
    bool single_key_pressed = false;
    // iterating backwards to prioritize the last pressed keys
    for (int i = scan_result.num_pressed - 1; i >= 0; --i)
    {

        const auto key = scan_result.pressed[i];
        const auto action = actions[key->row][key->col];
        if (action != nullptr)
        {
            if (action->is_single_key())
            {
                const auto code = action->sequence[0].key;
                single_key_report.add_key(code);

                const auto modifier = action->sequence[0].modifier;
                single_key_report.add_key(modifier);

                const auto media = action->sequence[0].media;
                single_key_report.add_key(media);
                single_key_pressed = true;
            }
            else
            {
                for (int j = 0; j < action->sequence_length; ++j)
                {
                    KeyReport report;
                    const auto code = action->sequence[j].key;
                    report.add_key(code);

                    const auto modifier = action->sequence[j].modifier;
                    report.add_key(modifier);

                    const auto media = action->sequence[j].media;
                    report.add_key(media);
                    key_queue.push(report);
                }
            }
        }
    }
    if (single_key_pressed)
    {
        key_queue.push(single_key_report);
    }
}

Action* KeyMap::get_action(int row, int col) const
{
    return actions[row][col];
}

bool KeyMap::load(const uint16_t* data, int size)
{
    if (!check_checksum(data, size))
    {
        return false;
    }

    if (!check_sequence_lengths(data, size))
    {
        return false;
    }

    // initialize all actions to null
    for (int i = 0; i < common::constants::NUM_ROWS; i++)
    {
        for (int j = 0; j < common::constants::NUM_COLS; j++)
        {
            actions[i][j] = nullptr;
        }
    }

    for (int i = 2; i < size;)
    {
        const uint16_t row = data[i++];
        const uint16_t col = data[i++];

        const uint16_t sequence_length = data[i++];

        KeyPress* sequence = new KeyPress[sequence_length];
        for (int j = 0; j < sequence_length; ++j)
        {
            const uint16_t key = data[i++];
            if (!util::key_is_valid_standard_key(key))
            {
                return false;
            }

            uint16_t modifier = data[i++];
            if (!util::key_is_valid_modifier(modifier))
            {
                return false;
            }

            uint16_t media = data[i++];
            if (!util::key_is_media(media))
            {
                return false;
            }

            sequence[j] = {key, modifier, media};
        }
        Action* action = new Action(sequence, sequence_length);
        actions[row][col] = action;
    }

    return true;
}

}
