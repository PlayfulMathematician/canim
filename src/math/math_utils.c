#include "canim/core.h"
#include "canim/math.h"
#include <math.h>
CANIM_API double lerp(double a, double b, double t) { return (b - a) * t + a; }
CANIM_API double clamp(double x, double lo, double hi) {
  if (x < lo) {
    return lo;
  }
  if (x > hi) {
    return hi;
  }
  return x;
}

CANIM_API bool nearly_equal(double a, double b) {
  return fabs(a - b) < EPSILON;
}
