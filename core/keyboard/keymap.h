#pragma once
#include "../util/queue.h"
#include "../../common/constants.h"
#include "keyscan.h"
#include "action.h"


namespace simulator
{
class SimulatorWindow;
class KeyboardState;
}

namespace core::keyboard
{

struct KeyReport
{
    uint16_t keys[common::constants::MAX_KEYREPORT_KEYS];
    uint16_t modifier = 0;
    uint16_t media = 0;
    uint8_t num_keys = 0;

    void add_key(uint16_t key);
};

typedef util::FixedSizeQueue<KeyReport, common::constants::MAX_QUEUED_KEY_EVENTS> KeyQueue;

class KeyMap
{
public:
    void translate_keyboard_scan_result(const KeyboardScanResult& scan_result, KeyQueue& key_queue) const;

    void load_default();
    void load(uint8_t* data, int size);

    friend class simulator::SimulatorWindow;
    friend class simulator::KeyboardState;

private:
    Action* actions[common::constants::NUM_ROWS][common::constants::NUM_COLS];
};

}
