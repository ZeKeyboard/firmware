#pragma once

#include "../../../device.h"
#include "../../keyboard/keyscan.h"
#include "../ledstate.h"
#include "scheme.h"
#include <cstdint>

namespace core::backlight::schemes
{

class GameOfLife : public Scheme
{
public:

    GameOfLife(Device& device);

    void reset() override;

    void update(const core::keyboard::KeyboardScanResult& scan_result,
        core::backlight::LEDState led_states[common::constants::TOTAL_NUM_LEDS]) override;
private:
    uint64_t it = 0;

    uint8_t grid[common::constants::NUM_ROWS][common::constants::NUM_COLS];

    uint8_t count_alive_neighbors(int8_t row, int8_t col) const;

    void run_one_evolution();

    bool was_alive(int8_t row, int8_t col) const;
    bool is_alive(int8_t row, int8_t col) const;

    void set_alive(int8_t row, int8_t col);
    void save_previous();

};

}
