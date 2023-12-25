#pragma once

#include <string>
#include <unordered_map>

namespace simulator
{

const std::unordered_map<uint16_t, std::string> KEY_CODES =
{
    {(0x01 | 0xE000), "LCtrl"},
    {(0x02 | 0xE000), "LShift"},
    {(0x04 | 0xE000), "LAlt"},
    {(0x08 | 0xE000), "LGui"},
    {(0x10 | 0xE000), "RCtrl"},
    {(0x20 | 0xE000), "RShift"},
    {(0x40 | 0xE000), "RAlt"},
    {(0x80 | 0xE000), "RGui"},
    {(0x81 | 0xE200), "PowerDown"},
    {(0x82 | 0xE200), "Sleep"},
    {(0x83 | 0xE200), "WakeUp"},
    {(0xB0 | 0xE400), "Play"},
    {(0xB1 | 0xE400), "Pause"},
    {(0xB2 | 0xE400), "Record"},
    {(0xB3 | 0xE400), "FastForward"},
    {(0xB4 | 0xE400), "Rewind"},
    {(0xB5 | 0xE400), "NextTrack"},
    {(0xB6 | 0xE400), "PrevTrack"},
    {(0xB7 | 0xE400), "Stop"},
    {(0xB8 | 0xE400), "Eject"},
    {(0xB9 | 0xE400), "RandomPlay"},
    {(0xCD | 0xE400), "PlayPause"},
    {(0xCE | 0xE400), "PlaySkip"},
    {(0xE2 | 0xE400), "Mute"},
    {(0xE9 | 0xE400), "VolumeInc"},
    {(0xEA | 0xE400), "VolumeDec"},
    {(4    | 0xF000), "A"},
    {(5    | 0xF000), "B"},
    {(6    | 0xF000), "C"},
    {(7    | 0xF000), "D"},
    {(8    | 0xF000), "E"},
    {(9    | 0xF000), "F"},
    {(10   | 0xF000), "G"},
    {(11   | 0xF000), "H"},
    {(12   | 0xF000), "I"},
    {(13   | 0xF000), "J"},
    {(14   | 0xF000), "K"},
    {(15   | 0xF000), "L"},
    {(16   | 0xF000), "M"},
    {(17   | 0xF000), "N"},
    {(18   | 0xF000), "O"},
    {(19   | 0xF000), "P"},
    {(20   | 0xF000), "Q"},
    {(21   | 0xF000), "R"},
    {(22   | 0xF000), "S"},
    {(23   | 0xF000), "T"},
    {(24   | 0xF000), "U"},
    {(25   | 0xF000), "V"},
    {(26   | 0xF000), "W"},
    {(27   | 0xF000), "X"},
    {(28   | 0xF000), "Y"},
    {(29   | 0xF000), "Z"},
    {(30   | 0xF000), "1"},
    {(31   | 0xF000), "2"},
    {(32   | 0xF000), "3"},
    {(33   | 0xF000), "4"},
    {(34   | 0xF000), "5"},
    {(35   | 0xF000), "6"},
    {(36   | 0xF000), "7"},
    {(37   | 0xF000), "8"},
    {(38   | 0xF000), "9"},
    {(39   | 0xF000), "0"},
    {(40   | 0xF000), "Enter"},
    {(41   | 0xF000), "Esc"},
    {(42   | 0xF000), "Backspace"},
    {(43   | 0xF000), "Tab"},
    {(44   | 0xF000), "Space"},
    {(45   | 0xF000), "-"},
    {(46   | 0xF000), "="},
    {(47   | 0xF000), "["},
    {(48   | 0xF000), "]"},
    {(49   | 0xF000), "\\"},
    {(50   | 0xF000), "NonUsNum"},
    {(51   | 0xF000), ";"},
    {(52   | 0xF000), "'"},
    {(53   | 0xF000), "~"},
    {(54   | 0xF000), ","},
    {(55   | 0xF000), "."},
    {(56   | 0xF000), "/"},
    {(57   | 0xF000), "CapsLock"},
    {(58   | 0xF000), "F1"},
    {(59   | 0xF000), "F2"},
    {(60   | 0xF000), "F3"},
    {(61   | 0xF000), "F4"},
    {(62   | 0xF000), "F5"},
    {(63   | 0xF000), "F6"},
    {(64   | 0xF000), "F7"},
    {(65   | 0xF000), "F8"},
    {(66   | 0xF000), "F9"},
    {(67   | 0xF000), "F10"},
    {(68   | 0xF000), "F11"},
    {(69   | 0xF000), "F12"},
    {(70   | 0xF000), "PrintScreen"},
    {(71   | 0xF000), "ScrollLock"},
    {(72   | 0xF000), "Pause"},
    {(73   | 0xF000), "Insert"},
    {(74   | 0xF000), "Home"},
    {(75   | 0xF000), "PageUp"},
    {(76   | 0xF000), "Delete"},
    {(77   | 0xF000), "End"},
    {(78   | 0xF000), "PageDown"},
    {(79   | 0xF000), "Right"},
    {(80   | 0xF000), "Left"},
    {(81   | 0xF000), "Down"},
    {(82   | 0xF000), "Up"},
    {(83   | 0xF000), "NumLock"},
    {(84   | 0xF000), "/"},
    {(85   | 0xF000), "*"},
    {(86   | 0xF000), "-"},
    {(87   | 0xF000), "+"},
    {(88   | 0xF000), "Enter"},
    {(89   | 0xF000), "1"},
    {(90   | 0xF000), "2"},
    {(91   | 0xF000), "3"},
    {(92   | 0xF000), "4"},
    {(93   | 0xF000), "5"},
    {(94   | 0xF000), "6"},
    {(95   | 0xF000), "7"},
    {(96   | 0xF000), "8"},
    {(97   | 0xF000), "9"},
    {(98   | 0xF000), "0"},
    {(99   | 0xF000), "."},
    {(100  | 0xF000), "<>"},
    {(101  | 0xF000), "Menu"},
    {(104  | 0xF000), "F13"},
    {(105  | 0xF000), "F14"},
    {(106  | 0xF000), "F15"},
    {(107  | 0xF000), "F16"},
    {(108  | 0xF000), "F17"},
    {(109  | 0xF000), "F18"},
    {(110  | 0xF000), "F19"},
    {(111  | 0xF000), "F20"},
    {(112  | 0xF000), "F21"},
    {(113  | 0xF000), "F22"},
    {(114  | 0xF000), "F23"},
    {(115  | 0xF000), "F24" },
};
}

