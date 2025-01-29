#pragma once

#include "scheme.h"
#include "../../../device.h"
#include <cmath>
#include <cstdint>
#include "../../../common/constants.h"

namespace core::backlight::schemes
{

constexpr float WATER_RESOLUTION = 5.0f;

constexpr int WATER_HEIGHT = util::ceil(common::constants::MAX_Y * WATER_RESOLUTION);
constexpr int WATER_WIDTH = util::ceil(common::constants::MAX_X * WATER_RESOLUTION);

struct WaterParticle
{
    int16_t speed = 0;
    int16_t pos = 0;
    int16_t prev_speed = 0;
    int16_t prev_pos = 0;

    inline void reset()
    {
        speed = 0;
        pos = 0;
        prev_speed = 0;
        prev_pos = 0;
    }
};

class Water : public Scheme
{
public:
    Water(Device& device) : Scheme{device} { }

    void reset() override;

    void update(const core::keyboard::KeyboardScanResult& scan_result,
        core::backlight::LEDState led_states[common::constants::TOTAL_NUM_LEDS]) override;

    void get_neighbors(WaterParticle* neighbors[4], int row, int col);
    void get_corner_neighbors(WaterParticle* neighbors[4], int row, int col);

    void react_to_keypress(const core::keyboard::KeyboardScanResult& scan_result);
    void update_water_physics();
    void write_colors(core::backlight::LEDState led_states[common::constants::TOTAL_NUM_LEDS]);

private:
    uint64_t it;

    WaterParticle particles[WATER_HEIGHT][WATER_WIDTH];
};

}
