#include "gameoflife.h"
#include "scheme.h"
#include <cstdint>
#include <iostream>

namespace core::backlight::schemes
{

constexpr int UPDATE_STRIDE = 15;

constexpr Color CELL_COLORS[9] = {
    {0.0, 0.0, 1.0},
    {0.0, 0.5, 0.5},
    {0.0, 0.7, 0.3},
    {0.0, 1.0, 0.0},
    {0.3, 0.7, 0.0},
    {0.5, 0.5, 0.0},
    {0.7, 0.3, 0.0},
    {0.9, 0.1, 0.0},
    {1.0, 0.0, 0.0}
};


GameOfLife::GameOfLife(Device& device) : Scheme(device) { }

void GameOfLife::reset()
{
    it = 0;

    for (int row = 0; row < common::constants::NUM_ROWS; ++row)
    {
        for (int col = 0; col < common::constants::NUM_COLS; ++col)
        {
            grid[row][col] = 0;
        }
    }

    // Start with glider
    set_alive(3, 5);
    set_alive(3, 6);
    set_alive(3, 7);
    set_alive(2, 7);
    set_alive(1, 6);
}

void GameOfLife::update(const core::keyboard::KeyboardScanResult& scan_result,
    core::backlight::LEDState led_states[common::constants::TOTAL_NUM_LEDS])
{
    it += 1;
    // update from keyboard
    for (int i = 0; i < scan_result.num_pressed; ++i)
    {
        const auto key = scan_result.pressed[i];
        set_alive(key->row, key->col);
    }

    if (it % UPDATE_STRIDE == 0)
    {
        run_one_evolution();
    }

    for (int i = 0; i < common::constants::TOTAL_NUM_LEDS; ++i)
    {
        auto& state = led_states[i];
        const auto desc = state.description;
        const auto key = desc->key;
        if (key != nullptr)
        {
            const auto row = key->row;
            const auto col = key->col;
            if (is_alive(row, col))
            {
                const auto num_neighbors = count_alive_neighbors(row, col);
                const auto color = CELL_COLORS[num_neighbors];
                state.color = color;
            }
            else
            {
                state.color = colors::BLACK;
            }
        }
    }
}

void GameOfLife::run_one_evolution()
{
    save_previous();

    for (int row = 0; row < common::constants::NUM_ROWS; ++row)
    {
        for (int col = 0; col < common::constants::NUM_COLS; ++col)
        {
            const auto num_neighbors = count_alive_neighbors(row, col);
            if (was_alive(row, col))
            {
                if (num_neighbors > 3 || num_neighbors < 2)
                {
                    // set the cell to dead
                    grid[row][col] &= 0xFE;
                }
                else
                {
                    // set the cell to alive
                    set_alive(row, col);
                }
            }
            else if (num_neighbors == 3)
            {
                // set the cell to alive
                set_alive(row, col);
            }
        }
    }
}

void GameOfLife::set_alive(int8_t row, int8_t col)
{
    grid[row][col] |= 0x01;
}


uint8_t GameOfLife::count_alive_neighbors(int8_t row, int8_t col) const
{
    uint8_t num_alive_neighbors = 0;

    for (int8_t dy = -1; dy < 2; ++dy)
    {
        for (int8_t dx = -1; dx < 2; ++dx)
        {
            if (row == 2 && col == 7)
            {
                std::cout << "haha great" << std::endl;
            }
            int8_t y = core::util::wrap_around(row + dy, 0, common::constants::NUM_ROWS - 1);
            int8_t x = core::util::wrap_around(col + dx, 0, common::constants::NUM_COLS - 1);

            // something seems to be wrong here
            if (was_alive(y, x) && !(dy == 0 && dx == 0))
            {
                num_alive_neighbors++;
            }
        }
    }
    return num_alive_neighbors;
}

bool GameOfLife::was_alive(int8_t row, int8_t col) const
{
    return (grid[row][col] & 0x02) != 0;
}

bool GameOfLife::is_alive(int8_t row, int8_t col) const
{
    return (grid[row][col] & 0x01) != 0;
}

void GameOfLife::save_previous()
{
    for (int row = 0; row < common::constants::NUM_ROWS; ++row)
    {
        for (int col = 0; col < common::constants::NUM_COLS; ++col)
        {
            bool alive = is_alive(row, col);
            grid[row][col] = alive ? 2 : 0;
        }
    }
}

}
