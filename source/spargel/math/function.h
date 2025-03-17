#pragma once

#include <spargel/base/attribute.h>

//
#include <math.h>

namespace spargel::math {

    SPARGEL_ALWAYS_INLINE inline float abs(float x) { return ::fabsf(x); }
    SPARGEL_ALWAYS_INLINE inline double abs(double x) { return ::fabs(x); }

    SPARGEL_ALWAYS_INLINE inline float sqrt(float x) { return ::sqrtf(x); }
    SPARGEL_ALWAYS_INLINE inline double sqrt(double x) { return ::sqrt(x); }

    SPARGEL_ALWAYS_INLINE inline float tan(float x) { return ::tanf(x); }

}  // namespace spargel::math
