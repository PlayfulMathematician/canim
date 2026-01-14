// SPDX-License-Identifier: MIT
#include "canim/core.h"
#include "canim/math.h"
#include <math.h>
CANIM_API CanimNumber canim_lerp(CanimNumber a, CanimNumber b, CanimNumber t) {
  return (b - a) * t + a;
}
CANIM_API CanimNumber canim_clamp(CanimNumber x, CanimNumber lo,
                                  CanimNumber hi) {
  if (x < lo) {
    return lo;
  }
  if (x > hi) {
    return hi;
  }
  return x;
}

CANIM_API bool canim_nearly_equal(CanimNumber a, CanimNumber b) {
  return fabs(a - b) < CANIM_EPSILON;
}
