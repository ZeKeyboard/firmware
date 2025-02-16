#include "interpolation.h"
#include <cmath>
#include <cstdint>
#include "../util/math_utils.h"

namespace core::backlight
{


static float index_image(const float* image, uint8_t image_width, uint8_t y, uint8_t x)
{
    return image[x + y * image_width];
}

float interpolate_image(
    const float* image,
    int image_height,
    int image_width,
    float image_x,
    float image_y,
    float sample_x,
    float sample_y)
{
    const float x = sample_x - image_x;
    const float y = sample_y - image_y;

    const int left_x = static_cast<int>(std::floor(x));
    const int top_y = static_cast<int>(std::floor(y));
    const float top_left =
        util::is_in_bounds(image_height, image_width, left_x, top_y)
        ? index_image(image, image_width, top_y, left_x) : 0.0f;

    const int right_x = static_cast<int>(util::always_ceil(x));
    const float top_right =
        util::is_in_bounds(image_height, image_width, right_x, top_y)
        ? index_image(image, image_width, top_y, right_x) : 0.0f;

    const int bottom_y = static_cast<int>(util::always_ceil(y));
    const float bottom_left =
        util::is_in_bounds(image_height, image_width, left_x, bottom_y)
        ? index_image(image, image_width, bottom_y, left_x) : 0.0f;

    const float bottom_right =
        util::is_in_bounds(image_height, image_width, right_x, bottom_y)
        ? index_image(image, image_width, bottom_y, right_x) : 0.0f;

    const float x_diff = right_x - left_x;
    const float y_diff = bottom_y - top_y;

    const float x_right_diff = (right_x - x) / x_diff;
    const float x_left_diff = (x - left_x) / x_diff;

    const float y_bottom_diff = (bottom_y - y) / y_diff;
    const float y_top_diff = (y - top_y) / y_diff;

    const float interp_x_top = x_right_diff * top_left + x_left_diff * top_right;
    const float interp_x_bottom = x_right_diff * bottom_left + x_left_diff * bottom_right;

    const float interp = interp_x_bottom * y_top_diff + interp_x_top * y_bottom_diff;

    return interp;
}

}
