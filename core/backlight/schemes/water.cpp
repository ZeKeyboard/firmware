#include "water.h"
#include <cmath>

namespace core::backlight::schemes
{

const float HUE_SPEED = 0.001f;
const uint8_t NUM_CORNERS = 4;
const float CORNER_DIST = 1.0 / sqrt(2);
const float NEIGHBOR_DENOMINATOR = 4 + 4/sqrt(2);
const float DAMPENING = 0.995f;
const uint8_t KEY_PRESS_RADIUS = 1 * WATER_RESOLUTION;
const int16_t PRESS_FORCE = 20000;
const float WATER_SPEED = 0.2;
const float SPEED_LIMIT = 1500.f;


void Water::reset()
{
    it = 0;

    for (int row = 0; row < WATER_HEIGHT; ++row)
    {
        for (int col = 0; col < WATER_WIDTH; ++col)
        {
            particles[row][col].reset();
        }
    }
}


void Water::update(const core::keyboard::KeyboardScanResult& scan_result,
    core::backlight::LEDState led_states[common::constants::TOTAL_NUM_LEDS])
{
    it++;

    react_to_keypress(scan_result);
    write_colors(led_states);
    update_water_physics();

    for (int row = 0; row < WATER_HEIGHT; ++row)
    {
        for (int col = 0; col < WATER_WIDTH; ++col)
        {
            WaterParticle* p = &particles[row][col];
            p->prev_pos = p->pos;
            p->prev_speed = p->speed;
        }
    }
}


void Water::write_colors(core::backlight::LEDState led_states[common::constants::TOTAL_NUM_LEDS])
{
    for (int i = 0; i < common::constants::TOTAL_NUM_LEDS; ++i)
    {
        auto led_state = &led_states[i];

        int particle_x = floor(led_state->description->x * WATER_RESOLUTION);
        int particle_y = floor(led_state->description->y * WATER_RESOLUTION);
        WaterParticle* p = &particles[particle_y][particle_x];

        const float amount = ((((float)p->pos) / 32767.0) + 1.0) / 2.0;
        const float hue = (cos(static_cast<float>(it) * HUE_SPEED) + 1.0f) / 2.0f;
        const Color color = Color::from_hsv(hue, 1.0f, std::min(1.0f, amount * amount * amount * 1.3f));

        led_state->color = color;
    }
}


void Water::react_to_keypress(const core::keyboard::KeyboardScanResult& scan_result)
{
    for (int i = 0; i < scan_result.num_just_pressed; ++i)
    {
        const common::LEDDescription pressed = scan_result.just_pressed[i]->get_associated_led();
        int particle_x = floor(pressed.x * WATER_RESOLUTION);
        int particle_y = floor(pressed.y * WATER_RESOLUTION);

        for (int row = std::max(particle_y - KEY_PRESS_RADIUS, 0); row < std::min(particle_y + KEY_PRESS_RADIUS, WATER_HEIGHT - 1); ++row)
        {
            for (int col = std::max(particle_x - KEY_PRESS_RADIUS, 0); col < std::min(particle_x + KEY_PRESS_RADIUS, WATER_WIDTH - 1); ++col)
            {
                particles[row][col].pos = PRESS_FORCE;
            }
        }
    }
}


void Water::update_water_physics()
{
    for (int row = 0; row < WATER_HEIGHT; ++row)
    {
        for (int col = 0; col < WATER_WIDTH; ++col)
        {
            WaterParticle* p = &particles[row][col];

            // make sure we still have the previous speed and position
            p->prev_speed = p->speed;
            p->prev_pos = p->pos;

            WaterParticle* neighbors[NUM_CORNERS];
            get_neighbors(neighbors, row, col);
            WaterParticle* corners[NUM_CORNERS];
            get_corner_neighbors(corners, row, col);
            float speed = 0;
            for (uint8_t i = 0; i < NUM_CORNERS; ++i)
            {
                speed += (float)neighbors[i]->prev_pos;
                speed += (((float)corners[i]->prev_pos) * CORNER_DIST);
            }
            float prev_pos_f = (float)p->prev_pos;
            float prev_speed_f = (float)p->prev_speed;
            speed = (speed / NEIGHBOR_DENOMINATOR) - prev_pos_f;
            float new_speed = (prev_speed_f + speed * WATER_SPEED) * DAMPENING;
            p->speed = (int16_t)util::clamp(new_speed, -SPEED_LIMIT, SPEED_LIMIT);

            float posf = ((float)p->pos) + new_speed;
            posf = util::clamp(posf, -32760.0f, 32760.0f);
            p->pos = (int16_t)posf;
        }
    }
}


void Water::get_neighbors(WaterParticle* neighbors[NUM_CORNERS], int row, int col)
{
    neighbors[0] = &particles[util::clamp(row + 1, 0, WATER_HEIGHT - 1)]
        [util::clamp(col, 0, WATER_WIDTH - 1)];
    neighbors[1] = &particles[util::clamp(row - 1, 0, WATER_HEIGHT - 1)]
        [util::clamp(col, 0, WATER_WIDTH - 1)];
    neighbors[2] = &particles[util::clamp(row, 0, WATER_HEIGHT - 1)]
        [util::clamp(col - 1, 0, WATER_WIDTH - 1)];
    neighbors[3] = &particles[util::clamp(row, 0, WATER_HEIGHT - 1)]
        [util::clamp(col + 1, 0, WATER_WIDTH - 1)];
}


void Water::get_corner_neighbors(WaterParticle* neighbors[NUM_CORNERS], int row, int col)
{
    neighbors[0] = &particles[util::clamp(row + 1, 0, WATER_HEIGHT - 1)]
        [util::clamp(col + 1, 0, WATER_WIDTH - 1)];
    neighbors[1] = &particles[util::clamp(row - 1, 0, WATER_HEIGHT - 1)]
        [util::clamp(col + 1, 0, WATER_WIDTH - 1)];
    neighbors[2] = &particles[util::clamp(row + 1, 0, WATER_HEIGHT - 1)]
        [util::clamp(col - 1, 0, WATER_WIDTH - 1)];
    neighbors[3] = &particles[util::clamp(row - 1, 0, WATER_HEIGHT - 1)]
        [util::clamp(col - 1, 0, WATER_WIDTH - 1)];
}

}
