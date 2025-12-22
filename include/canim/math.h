#pragma once
#include "canim/core.h"
#include <stdbool.h>
CANIM_API double clamp(double x, double lo, double hi);
CANIM_API double lerp(double a, double b, double t);
CANIM_API bool nearly_equal(double a, double b);
