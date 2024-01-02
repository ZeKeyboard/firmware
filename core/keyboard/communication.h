#pragma once

#include "keymap.h"

namespace core::keyboard::communication
{
void send_key_report(KeyQueue& key_queue, Device& device);
}

