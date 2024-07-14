#pragma once

#include "keymap.h"

namespace core::keyboard::communication
{

void send_mouse_commands(MouseState& mouseState, Device& device);

void send_key_report(KeyQueue& key_queue, Device& device);

}

