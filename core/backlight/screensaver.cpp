#include "screensaver.h"
#include "interpolation.h"

namespace core::backlight
{

const float SPEED = 0.01;
constexpr float HUE_SPEED = 0.001f;

const float IMAGE[]
{
    0.2f, 1.0f, 0.2f,
    1.0f, 1.0f, 1.0f,
    0.2f, 1.0f, 0.2f
};

const int IMAGE_HEIGHT = 3;
const int IMAGE_WIDTH = 3;

void ScreenSaver::init()
{
    position = {0.0f, 0.0f};
    velocity = {SPEED, SPEED * 0.9f};
}

void ScreenSaver::update()
{
    auto new_position = position + velocity;

    if (new_position.x <= 0.0f || new_position.x >= common::constants::MAX_X)
    {
        velocity.flip_x();
    }
    if (new_position.y <= 0.0f || new_position.y >= common::constants::MAX_Y)
    {
        velocity.flip_y();
    }

    position = position + velocity;
    it++;
}

void ScreenSaver::draw(LEDState led_states[common::constants::TOTAL_NUM_LEDS])
{
    const float hue = (cos(static_cast<float>(it) * HUE_SPEED) + 1.0f) / 2.0f;

    for (int i = 0; i < common::constants::TOTAL_NUM_LEDS; ++i)
    {
        auto state = &led_states[i];
        float y = state->description->y;
        float x = state->description->x;
        float val = interpolate_image(IMAGE, IMAGE_HEIGHT, IMAGE_WIDTH, position.x, position.y, x, y);

        state->color = Color::from_hsv(hue, 1.0f, val);
    }
}

}
