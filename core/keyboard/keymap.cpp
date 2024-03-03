#include "keymap.h"
#include "keyutils.h"


namespace core::keyboard
{


const char* KEYMAP_FILENAME = "Configuration.zkb";


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
        i += 3;

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

    const int expected_size = 2 + total_number_of_keys * 4 + total_sequence_length * 3;

    if (size != expected_size)
    {
        return false;
    }
    return true;
}


void KeyMap::load_default()
{
    // initialize all actions to null
    for (int layer = 0; layer < common::constants::MAX_NUM_LAYERS; layer++)
    {
        for (int row = 0; row < common::constants::NUM_ROWS; row++)
        {
            for (int col = 0; col < common::constants::NUM_COLS; col++)
            {
                actions[layer][row][col] = nullptr;
            }
        }
    }

    for (int row = 0; row < common::constants::NUM_ROWS; row++)
    {
        for (int col = 0; col < common::constants::NUM_COLS; col++)
        {
            const auto key_props = common::constants::KEY_PROPERTIES_BY_ROW_COL[row][col];
            if (key_props != nullptr)
            {
                actions[0][row][col] = new Action(key_props->default_key);
            }
        }
    }
}


int KeyMap::get_hold_layer(const KeyboardScanResult& scan_result) const
{
    for (int i = 0; i < scan_result.num_pressed; ++i)
    {
        const auto key = scan_result.pressed[i];
        const auto action = get_action(0, key->row, key->col);
        if (action != nullptr && action->is_single_key())
        {
            const auto code = action->sequence[0].key;
            if (util::key_is_layer_hold_modifier(code))
            {
                return util::get_layer_modifier_layer(code);
            }
        }
    }
    return -1;
}


void KeyMap::update_current_layer(const KeyboardScanResult& scan_result)
{
    for (int i = 0; i < scan_result.num_pressed; ++i)
    {
        const auto key = scan_result.pressed[i];
        const auto action = get_action(0, key->row, key->col);
        if (action != nullptr && action->is_single_key())
        {
            const auto code = action->sequence[0].key;
            if (util::key_is_layer_toggle_modifier(code))
            {
                const auto layer = util::get_layer_modifier_layer(code);
                current_layer = current_layer == layer ? 0 : layer;
            }
        }
    }
}


void KeyMap::translate_keyboard_scan_result(const KeyboardScanResult& scan_result, KeyQueue& key_queue)
{
    /*
     * This function implements the following logic:
     * For each key in the scan result:
     * If the keys are single keys (not part of a sequence),
     * they should all be sent together in a single report. This is because the user
     * might be holding down several keys together.
     * If the keys are part of a sequence, they should be sent in separate report, all queued up. This is because they need to be sent separately for the computer to intepret them as separate keypresses.
     * Before everything, the presence of layer modifiers are checked and handled accordingly.
     */

    KeyReport single_key_report;
    bool single_key_pressed = false;

    update_current_layer(scan_result);
    const int hold_layer_modifier = get_hold_layer(scan_result);
    int layer_to_use = hold_layer_modifier != -1 ? hold_layer_modifier : current_layer;

    // iterating backwards to prioritize the last pressed keys
    for (int i = scan_result.num_pressed - 1; i >= 0; --i)
    {
        const auto key = scan_result.pressed[i];
        const auto action = get_action(layer_to_use, key->row, key->col);
        if (action != nullptr)
        {
            if (action->is_single_key())
            {
                const auto code = action->sequence[0].key;
                if (util::key_is_valid_standard_key(code))
                {
                    // this check is necessary since the key might be a layer modifier
                    single_key_report.add_key(code);
                }

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
    if (single_key_pressed && single_key_report.num_keys > 0)
    {
        key_queue.push(single_key_report);
    }
}


Action* KeyMap::get_action(int layer, int row, int col) const
{
    const auto action = actions[layer][row][col];
    if (action == nullptr && layer_fallback)
    {
        return actions[0][row][col];
    }
    return action;
}


bool KeyMap::deserialize_keymap(const uint16_t* data, int size)
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
    for (int layer = 0; layer < common::constants::MAX_NUM_LAYERS; layer++)
    {
        for (int row = 0; row < common::constants::NUM_ROWS; row++)
        {
            for (int col = 0; col < common::constants::NUM_COLS; col++)
            {
                actions[layer][row][col] = nullptr;
            }
        }
    }

    for (int i = 2; i < size;)
    {
        const uint16_t layer = data[i++];
        const uint16_t row = data[i++];
        const uint16_t col = data[i++];

        const uint16_t sequence_length = data[i++];

        KeyPress* sequence = new KeyPress[sequence_length];
        for (int j = 0; j < sequence_length; ++j)
        {
            const uint16_t key = data[i++];
            if (!util::key_is_valid_standard_key(key)
                && !util::key_is_layer_hold_modifier(key)
                && !util::key_is_layer_toggle_modifier(key))
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
        actions[layer][row][col] = action;
    }

    return true;
}


bool KeyMap::load_from_sd_else_default(Device& device)
{
    char* buffer;
    uint32_t num_read_bytes;
    const bool success = device.sd_read(KEYMAP_FILENAME, buffer, num_read_bytes);
    if (success)
    {
        const uint16_t* data = reinterpret_cast<const uint16_t*>(buffer);
        const int size = num_read_bytes / 2;
        const bool success = deserialize_keymap(data, size);
        delete[] buffer;
        if (success)
        {
            return true;
        }
    }
    load_default();
    return false;
}

}
