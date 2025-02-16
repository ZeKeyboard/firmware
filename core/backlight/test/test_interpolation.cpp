#include <catch_amalgamated.hpp>
#include <cmath>
#include <cstdio>
#include "../interpolation.h"

static void assert_almost_equal(float f1, float f2, float granularity = 0.0001)
{
    bool almost_equal = std::fabs(f1 - f2) < granularity;
    if (!almost_equal)
    {
        char message[64];
        snprintf(message, sizeof(message), "%f != %f", f1, f2);
        FAIL(message);
    }
}

TEST_CASE("Test interpolation", "[Interpolation]")
{
    const float image[4] =
    {
        1.0f, 2.0f,
        3.0f, 4.0f
    };

    SECTION("Test center")
    {
        float res1 = core::backlight::interpolate_image(image, 2, 2, 1, 0, 1.5, 0.5);
        float res2 = core::backlight::interpolate_image(image, 2, 2, 0, 0, 0.5, 0.5);
        assert_almost_equal(res1, res2);
        assert_almost_equal(res1, 2.5f);
    }

    SECTION("Test corners")
    {
        float res1 = core::backlight::interpolate_image(image, 2, 2, 1, 1, 1, 1);
        float res2 = core::backlight::interpolate_image(image, 2, 2, 0, 0, 0, 0);
        assert_almost_equal(res1, res2);
        assert_almost_equal(res1, 1.0f);

        float res3 = core::backlight::interpolate_image(image, 2, 2, 0, -1, 1, 0);
        float res4 = core::backlight::interpolate_image(image, 2, 2, 0, 0, 1, 1);
        assert_almost_equal(res3, res4);
        assert_almost_equal(res3, 4.0f);

        float res5 = core::backlight::interpolate_image(image, 2, 2, -1, 0, 0, 0);
        float res6 = core::backlight::interpolate_image(image, 2, 2, 0, 0, 1, 0);
        assert_almost_equal(res5, res6);
        assert_almost_equal(res5, 2.0f);
    }

    SECTION("Test outside")
    {
        float res1 = core::backlight::interpolate_image(image, 2, 2, 0, 0, 5, 5);
        float res2 = core::backlight::interpolate_image(image, 2, 2, 0, 0, -2, -2);
        assert_almost_equal(res1, res2);
        assert_almost_equal(res1, 0.0f);

        float res3 = core::backlight::interpolate_image(image, 2, 2, 0, 0, -0.5, -0.5);

        REQUIRE(res3 > 0.0f);
        REQUIRE(res3 < 1.0f);
    }
}
