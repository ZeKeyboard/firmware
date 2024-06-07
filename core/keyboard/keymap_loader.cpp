#include "keymap_loader.h"
#include "keyutils.h"
#include "../util/buffer_utils.h"


namespace core::keyboard
{


void KeyMapLoader::load_default(KeyMap& keymap)
{
    // initialize all actions to null
    for (int layer = 0; layer < common::constants::MAX_NUM_LAYERS; layer++)
    {
        for (int row = 0; row < common::constants::NUM_ROWS; row++)
        {
            for (int col = 0; col < common::constants::NUM_COLS; col++)
            {
                keymap.actions[layer][row][col] = nullptr;
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
                keymap.actions[0][row][col] = new Action(key_props->default_key);
            }
        }
    }
}


bool KeyMapLoader::check_sequence_lengths(const uint16_t* data, int size)
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


bool KeyMapLoader::check_checksum(const uint16_t* data, int size)
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


bool KeyMapLoader::load_from_sd_else_default(Device& device, KeyMap& keymap)
{
    char* ascii_buffer;
    uint32_t num_read_ascii_chars;
    const bool success = device.sd_read(common::constants::KEYMAP_FILENAME,
                                        ascii_buffer, num_read_ascii_chars);

    char* buffer;
    int num_read_bytes;
    core::util::ascii_buffer_to_hex_buffer(
        ascii_buffer, buffer, num_read_ascii_chars, num_read_bytes);

    if (success)
    {
        const uint16_t* data = reinterpret_cast<const uint16_t*>(buffer);
        const int size = num_read_bytes / 2;
        const bool success = deserialize_keymap(data, size, keymap);
        delete[] buffer;
        if (success)
        {
            return true;
        }
    }
    load_default(keymap);
    return false;
}


bool KeyMapLoader::deserialize_keymap(const uint16_t* data, int size, KeyMap& keymap)
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
                keymap.actions[layer][row][col] = nullptr;
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
            if (!util::key_is_valid_non_modifier_and_non_media(key))
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
        keymap.actions[layer][row][col] = action;
    }

    return true;
}


}
