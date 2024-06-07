#pragma once

#include <stdint.h>
#include "keymap.h"


namespace core::keyboard
{


/**
 * Class for loading keymaps from the SD card. The reason for making this a class rather than
 * stand-alone functions is so that keymap can friend it and access its private members.
 */
class KeyMapLoader
{
public:

    /**
     * Load the keymap from the SD card if it exists, otherwise load the default keymap.
     * @param device The device to load the keymap for.
     * @return True if the keymap was loaded from the SD card, false if the default keymap was loaded.
     */
    static bool load_from_sd_else_default(Device& device, KeyMap& keymap);

    static bool deserialize_keymap(const uint16_t* data, int size, KeyMap& keymap);

private:
    static bool check_checksum(const uint16_t* data, int size);
    static bool check_sequence_lengths(const uint16_t* data, int size);
    static void load_default(KeyMap& keymap);

};

}
