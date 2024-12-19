#include <Arduino.h>
#include "core/firmware.h"
#include "teensy_device.h"
#include "teensy4ledcontroller.h"
#include "common/constants.h"

CRGB leds[common::constants::TOTAL_NUM_LEDS];
byte pinList[1] = { 38 };
DMAMEM uint8_t displayMemory[common::constants::TOTAL_NUM_LEDS * 3];
uint8_t drawingMemory[common::constants::TOTAL_NUM_LEDS * 3];
OctoWS2811 octo(common::constants::TOTAL_NUM_LEDS, displayMemory, drawingMemory, WS2811_RGB | WS2811_800kHz, 1, pinList);
CTeensy4Controller<GRB, WS2811_800kHz>* pcontroller;

TeensyDevice device{leds};
core::Firmware firmware{device};

void setup()
{
    device.sd_init();
    octo.begin();
    pcontroller = new CTeensy4Controller<GRB, WS2811_800kHz>(&octo);
    FastLED.setBrightness(127);
    FastLED.addLeds(pcontroller, leds, common::constants::TOTAL_NUM_LEDS);

    FastLED.clear();
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 800);
    delay(50);
    FastLED.show();
    device.serial_begin(9600);
}

void loop()
{
    firmware.update();
}
