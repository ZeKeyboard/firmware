#include "keymap.h"
#include "keyutils.h"


namespace core::keyboard
{

void KeyReport::add_key(uint16_t key)
{
    if (util::key_is_standard_key(key))
    {
        if (num_keys < common::constants::MAX_KEYREPORT_KEYS)
        {
            keys[num_keys++] = key;
        }
    }
    else if (util::key_is_modifier(key))
    {
        modifier |= key;
    }
    else if (util::key_is_media(key))
    {
        media = key;
    }
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
    // TODO: if it's a single key, it should be combined with the simultaneously pressed keys, but if it's a sequence, it should override the others

    // iterating backwards to prioritize the last pressed keys
    KeyReport report;
    for (int i = scan_result.num_pressed - 1; i >= 0; --i)
    {

        const auto key = scan_result.pressed[i];
        const auto action = actions[key->row][key->col];
        if (action != nullptr)
        {
            if (action->is_single_key())
            {
                const auto code = action->get_single_key();
                report.add_key(code);
            }
        }
    }
    // TODO do special handling for sequences
    key_queue.push(report);
}


void KeyMap::load(uint8_t* data, int size)
{
    // TODO: implement
}

}
