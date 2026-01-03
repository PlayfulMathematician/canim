// SPDX-License-Identifier: AGPL-3.0
#pragma once
#include "canim/core.h"
#include <stdbool.h>
CANIM_API double canim_clamp(double x, double lo, double hi);
CANIM_API double canim_lerp(double a, double b, double t);
CANIM_API bool canim_nearly_equal(double a, double b);
