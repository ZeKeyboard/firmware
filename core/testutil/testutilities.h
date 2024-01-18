#pragma once

#include <cmath>

namespace testutil
{

inline bool float_equals(float f1, float f2, float delta = 0.00001)
{
    return fabs(f1 - f2) < delta;
}

}
