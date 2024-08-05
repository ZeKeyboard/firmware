#pragma once
#include "../util/queue.h"
#include "../../common/constants.h"
#include "keyscan.h"
#include "action.h"
#include "mouse.h"


namespace core::keyboard
{

struct KeyReport
{
    uint16_t keys[common::constants::MAX_KEYREPORT_KEYS];
    uint16_t modifier = 0xE000;
    uint16_t media = 0xE400;
    uint8_t num_keys = 0;

    void add_key(uint16_t key);
};

typedef util::FixedSizeQueue<KeyReport, common::constants::MAX_QUEUED_KEY_EVENTS> KeyQueue;


class KeyMap
{
    friend class KeyMapLoader;

public:
    void translate_keyboard_scan_result(
        const KeyboardScanResult& scan_result, KeyQueue& key_queue, MouseState& mouse);

    /**
     * Returns the action at the given layer, row, and column.
     * If there is no action at the given location and the layer is not the base layer,
     * it returns the action at the base layer. If there is nothing there either it
     * returns nullptr.
     */
    Action* get_action(int layer, int row, int col) const;

    int current_layer = 0;

private:

    void load_default();

    bool just_toggled_layer = false;

    // TODO make this configurable (see issue #1)
    bool layer_fallback = false;

    Action* actions[common::constants::MAX_NUM_LAYERS][common::constants::NUM_ROWS][common::constants::NUM_COLS];

    int get_hold_layer(const KeyboardScanResult& scan_result) const;

    /**
     * Updates the current layer based on whether the scan result contains a toggle layer key.
     */
    void update_current_layer(const KeyboardScanResult& scan_result);

    /**
     * Extracts the key from the action and adds it to the key report.
     * Returns true if the action is a single key press.
     */
    bool extract_single_key(const Action* action, KeyReport& single_key_report) const;

    /**
     * Reads the mouse keys from the scan result and updates the mouse state.
     */
    void read_mouse_keys(const KeyboardScanResult& scan_result, MouseState& mouse) const;

};

}
