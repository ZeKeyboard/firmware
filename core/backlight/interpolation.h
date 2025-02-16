#pragma once

namespace core::backlight
{

float interpolate_image(
    const float* image,
    int image_height,
    int image_width,
    float image_x,
    float image_y,
    float sample_x,
    float sample_y);

}
