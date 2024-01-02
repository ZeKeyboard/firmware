#include "communication.h"

namespace core::keyboard::communication
{

void send_key_report(KeyQueue& key_queue, Device& device)
{
    if (key_queue.size() > 0)
    {
        const KeyReport report = key_queue.front();
        for (unsigned i = 0; i < common::constants::MAX_KEYREPORT_KEYS; ++i)
        {
            const auto code = i < report.num_keys ? report.keys[i] : 0;
            device.set_keyboard_key_by_index(i, code);
        }
        device.set_keyboard_modifier(report.modifier);
        device.set_keyboard_media(report.media);
        device.keyboard_send();
        key_queue.pop();
    }
    else
    {
        for (unsigned i = 0; i < common::constants::MAX_KEYREPORT_KEYS; ++i)
        {
            device.set_keyboard_key_by_index(i, 0);
        }
        device.set_keyboard_modifier(0);
        device.set_keyboard_media(0);
        device.keyboard_send();
    }
}

}
