#include "keymap.h"
#include "keyutils.h"


namespace core::keyboard
{

void KeyReport::add_key(uint16_t key)
{
    if (util::key_is_valid_standard_key(key)
        && num_keys < common::constants::MAX_KEYREPORT_KEYS)
    {
        keys[num_keys++] = key;
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
                return util::get_layer_hold_modifier_layer(code);
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
                const auto layer = util::get_layer_toggle_modifier_layer(code);
                current_layer = current_layer == layer ? 0 : layer;
            }
        }
    }
}


bool KeyMap::extract_single_key(const Action* action, KeyReport& single_key_report)
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
        return true;
    }
    return false;
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
            single_key_pressed |= extract_single_key(action, single_key_report);
        }
    }


    // handle sequences, these should start only once
    for (int i = 0; i < scan_result.num_just_pressed; ++i)
    {
        const auto key = scan_result.just_pressed[i];
        const auto action = get_action(layer_to_use, key->row, key->col);
        if (action != nullptr && !action->is_single_key())
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

                // Add an empty report between each key, to ensure that the computer
                // interprets them as separate keypresses. Otherwise double letters will
                // be interpreted as a single letters.
                key_queue.push({});
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

}
