#pragma once

#include <stdint.h>
#include "../../common/constants.h"


namespace core::keyboard::util
{

/**
 * This array is used to check if a standard keycode is valid.
 */
const bool IS_KEYCODE_VALID[116]
{
    false,  // nothing
    false,  // nothing
    false,  // nothing
    false,  // nothing
    true,   // "KEY_A":                    4    | 0xF000
    true,   // "KEY_B":                    5    | 0xF000
    true,   // "KEY_C":                    6    | 0xF000
    true,   // "KEY_D":                    7    | 0xF000
    true,   // "KEY_E":                    8    | 0xF000
    true,   // "KEY_F":                    9    | 0xF000
    true,   // "KEY_G":                    10   | 0xF000
    true,   // "KEY_H":                    11   | 0xF000
    true,   // "KEY_I":                    12   | 0xF000
    true,   // "KEY_J":                    13   | 0xF000
    true,   // "KEY_K":                    14   | 0xF000
    true,   // "KEY_L":                    15   | 0xF000
    true,   // "KEY_M":                    16   | 0xF000
    true,   // "KEY_N":                    17   | 0xF000
    true,   // "KEY_O":                    18   | 0xF000
    true,   // "KEY_P":                    19   | 0xF000
    true,   // "KEY_Q":                    20   | 0xF000
    true,   // "KEY_R":                    21   | 0xF000
    true,   // "KEY_S":                    22   | 0xF000
    true,   // "KEY_T":                    23   | 0xF000
    true,   // "KEY_U":                    24   | 0xF000
    true,   // "KEY_V":                    25   | 0xF000
    true,   // "KEY_W":                    26   | 0xF000
    true,   // "KEY_X":                    27   | 0xF000
    true,   // "KEY_Y":                    28   | 0xF000
    true,   // "KEY_Z":                    29   | 0xF000
    true,   // "KEY_1":                    30   | 0xF000
    true,   // "KEY_2":                    31   | 0xF000
    true,   // "KEY_3":                    32   | 0xF000
    true,   // "KEY_4":                    33   | 0xF000
    true,   // "KEY_5":                    34   | 0xF000
    true,   // "KEY_6":                    35   | 0xF000
    true,   // "KEY_7":                    36   | 0xF000
    true,   // "KEY_8":                    37   | 0xF000
    true,   // "KEY_9":                    38   | 0xF000
    true,   // "KEY_0":                    39   | 0xF000
    true,   // "KEY_ENTER":                40   | 0xF000
    true,   // "KEY_ESC":                  41   | 0xF000
    true,   // "KEY_BACKSPACE":            42   | 0xF000
    true,   // "KEY_TAB":                  43   | 0xF000
    true,   // "KEY_SPACE":                44   | 0xF000
    true,   // "KEY_MINUS":                45   | 0xF000
    true,   // "KEY_EQUAL":                46   | 0xF000
    true,   // "KEY_LEFT_BRACE":           47   | 0xF000
    true,   // "KEY_RIGHT_BRACE":          48   | 0xF000
    true,   // "KEY_BACKSLASH":            49   | 0xF000
    true,   // "KEY_NON_US_NUM":           50   | 0xF000
    true,   // "KEY_SEMICOLON":            51   | 0xF000
    true,   // "KEY_QUOTE":                52   | 0xF000
    true,   // "KEY_TILDE":                53   | 0xF000
    true,   // "KEY_COMMA":                54   | 0xF000
    true,   // "KEY_PERIOD":               55   | 0xF000
    true,   // "KEY_SLASH":                56   | 0xF000
    true,   // "KEY_CAPS_LOCK":            57   | 0xF000
    true,   // "KEY_F1":                   58   | 0xF000
    true,   // "KEY_F2":                   59   | 0xF000
    true,   // "KEY_F3":                   60   | 0xF000
    true,   // "KEY_F4":                   61   | 0xF000
    true,   // "KEY_F5":                   62   | 0xF000
    true,   // "KEY_F6":                   63   | 0xF000
    true,   // "KEY_F7":                   64   | 0xF000
    true,   // "KEY_F8":                   65   | 0xF000
    true,   // "KEY_F9":                   66   | 0xF000
    true,   // "KEY_F10":                  67   | 0xF000
    true,   // "KEY_F11":                  68   | 0xF000
    true,   // "KEY_F12":                  69   | 0xF000
    true,   // "KEY_PRINTSCREEN":          70   | 0xF000
    true,   // "KEY_SCROLL_LOCK":          71   | 0xF000
    true,   // "KEY_PAUSE":                72   | 0xF000
    true,   // "KEY_INSERT":               73   | 0xF000
    true,   // "KEY_HOME":                 74   | 0xF000
    true,   // "KEY_PAGE_UP":              75   | 0xF000
    true,   // "KEY_DELETE":               76   | 0xF000
    true,   // "KEY_END":                  77   | 0xF000
    true,   // "KEY_PAGE_DOWN":            78   | 0xF000
    true,   // "KEY_RIGHT":                79   | 0xF000
    true,   // "KEY_LEFT":                 80   | 0xF000
    true,   // "KEY_DOWN":                 81   | 0xF000
    true,   // "KEY_UP":                   82   | 0xF000
    true,   // "KEY_NUM_LOCK":             83   | 0xF000
    true,   // "KEYPAD_SLASH":             84   | 0xF000
    true,   // "KEYPAD_ASTERIX":           85   | 0xF000
    true,   // "KEYPAD_MINUS":             86   | 0xF000
    true,   // "KEYPAD_PLUS":              87   | 0xF000
    true,   // "KEYPAD_ENTER":             88   | 0xF000
    true,   // "KEYPAD_1":                 89   | 0xF000
    true,   // "KEYPAD_2":                 90   | 0xF000
    true,   // "KEYPAD_3":                 91   | 0xF000
    true,   // "KEYPAD_4":                 92   | 0xF000
    true,   // "KEYPAD_5":                 93   | 0xF000
    true,   // "KEYPAD_6":                 94   | 0xF000
    true,   // "KEYPAD_7":                 95   | 0xF000
    true,   // "KEYPAD_8":                 96   | 0xF000
    true,   // "KEYPAD_9":                 97   | 0xF000
    true,   // "KEYPAD_0":                 98   | 0xF000
    true,   // "KEYPAD_PERIOD":            99   | 0xF000
    true,   // "KEY_NON_US_BS":            100  | 0xF000
    true,   // "KEY_MENU":                 101  | 0xF000
    false,  // nothing
    false,  // nothing
    true,   // "KEY_F13":                  104  | 0xF000
    true,   // "KEY_F14":                  105  | 0xF000
    true,   // "KEY_F15":                  106  | 0xF000
    true,   // "KEY_F16":                  107  | 0xF000
    true,   // "KEY_F17":                  108  | 0xF000
    true,   // "KEY_F18":                  109  | 0xF000
    true,   // "KEY_F19":                  110  | 0xF000
    true,   // "KEY_F20":                  111  | 0xF000
    true,   // "KEY_F21":                  112  | 0xF000
    true,   // "KEY_F22":                  113  | 0xF000
    true,   // "KEY_F23":                  114  | 0xF000
    true    // "KEY_F24":                  115  | 0xF000
};

inline bool key_is_blank(uint16_t key)
{
    return (key & 0x00FF) == 0;
}

inline bool key_is_valid_modifier(uint16_t key)
{
    return (key & 0xFF00) == 0xE000;
}

inline bool key_is_media(uint16_t key)
{
    return (key & 0xFF00) == 0xE400;
}

inline bool key_is_valid_standard_key(uint16_t key)
{
    if ((key & 0xFF00) != 0xF000)
    {
        return false;
    }
    const uint8_t code = key & 0x00FF;
    return code == 0 || (code < 116 && IS_KEYCODE_VALID[code]);
}

inline bool key_is_system_key(uint16_t key)
{
    return (key & 0xFF00) == 0xE200;
}

inline uint8_t get_layer_hold_modifier_layer(uint16_t key)
{
    return (key & 0x00FF) - 129;
}

inline uint8_t get_layer_toggle_modifier_layer(uint16_t key)
{
    return (key & 0x00FF) - 132;
}

inline bool key_is_layer_hold_modifier(uint16_t key)
{
    if ((key & 0xFF00) != common::constants::LAYER_HOLD_MODIFIER)
    {
        return false;
    }
    return get_layer_hold_modifier_layer(key) < common::constants::MAX_NUM_LAYERS;
}

inline bool key_is_layer_toggle_modifier(uint16_t key)
{
    if ((key & 0xFF00) != common::constants::LAYER_TOGGLE_MODIFIER)
    {
        return false;
    }
    return get_layer_toggle_modifier_layer(key) < common::constants::MAX_NUM_LAYERS;
}

inline bool key_is_mouse_key(uint16_t key)
{
    uint8_t code = key & 0x00FF;
    return code <= common::constants::MAX_MOUSE_CODE && code >= 116;
}

inline bool key_is_control_key(uint16_t key)
{
    return (key & 0xFF00) == common::constants::CONTROL_BASE_CODE;
}

inline bool key_is_valid_non_modifier_and_non_media(uint16_t key)
{
    return
        key_is_valid_standard_key(key) ||
        key_is_layer_toggle_modifier(key) ||
        key_is_layer_hold_modifier(key) ||
        key_is_mouse_key(key) ||
        key_is_control_key(key);
}

}
