#include "keymap_loader.h"
#include "keyutils.h"
#include "../util/buffer_utils.h"
#include <cstdint>


namespace core::keyboard
{


const uint64_t SETTINGS_START_WORD = 0xDEADBEEFDEADBEEF;

const uint16_t MOUSE_SPEED_NUMBER = 0;
const uint16_t MOUSE_ACCELERATION_NUMBER = 1;
const uint16_t HIGHLIGHT_LAYER_KEYS_NUMBER = 2;


struct DataProperties
{
    uint16_t* settings_start;
    int keymap_size;
    int settings_size;
};


DataProperties find_keymap_settings_split(const uint16_t* data, int size)
{
    DataProperties properties;
    properties.settings_start = nullptr;
    properties.keymap_size = 0;
    properties.settings_size = 0;

    for (int i = 0; i < size - 1; i++)
    {
        const uint64_t word =
            data[i + 3]
            | (static_cast<uint64_t>(data[i + 2]) << 16)
            | (static_cast<uint64_t>(data[i + 1]) << 32)
            | (static_cast<uint64_t>(data[i]) << 48);
        if (word == SETTINGS_START_WORD)
        {
            properties.settings_start = const_cast<uint16_t*>(&data[i + 4]);
            properties.keymap_size = i;
            properties.settings_size = size - i - 4;
            break;
        }
    }

    properties.keymap_size = properties.settings_start == nullptr
        ? size
        : properties.keymap_size;

    return properties;
}


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


bool KeyMapLoader::load_from_sd_else_default(Device& device, KeyMap& keymap, Settings& settings)
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
        const auto properties = find_keymap_settings_split(data, size);
        const bool keymap_success = deserialize_keymap(data, properties.keymap_size, keymap);
        bool settings_success = true;
        if (properties.settings_start != nullptr)
        {
            settings_success = deserialize_settings(properties.settings_start, properties.settings_size, settings);
        }
        delete[] buffer;
        if (keymap_success && settings_success)
        {
            return true;
        }
    }
    load_default(keymap);
    return false;
}


bool KeyMapLoader::deserialize_settings(const uint16_t* data, int size, Settings& settings)
{
    if (!check_settings_checksum(data, size))
    {
        return false;
    }

    const int num_settings = data[0];

    const uint16_t* settings_ptr = &data[2];
    for (int i = 0; i < num_settings * 2; i += 2)
    {
        const uint16_t setting_number = settings_ptr[i];
        const uint16_t setting_value = settings_ptr[i + 1];

        if (setting_number == MOUSE_SPEED_NUMBER)
        {
            settings.mouse_speed = setting_value;
        }
        else if (setting_number == MOUSE_ACCELERATION_NUMBER)
        {
            settings.mouse_acceleration = setting_value;
        }
        else if (setting_number == HIGHLIGHT_LAYER_KEYS_NUMBER)
        {
            settings.highlight_layer_keys = setting_value;
        }
    }

    return true;
}


bool KeyMapLoader::check_settings_checksum(const uint16_t* data, int size)
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
