// SPDX-License-Identifier: MIT
#include "canim/core.h"
#include "canim/math.h"
#include <math.h>

CANIM_API CanimVec2 canim_add_vec2(CanimVec2 a, CanimVec2 b) {
  return (CanimVec2){.x = a.x + b.x, .y = a.y + b.y};
}

CANIM_API CanimVec2 canim_negative_vec2(CanimVec2 a) {
  return (CanimVec2){.x = -a.x, .y = -a.y};
}

CANIM_API CanimVec2 canim_sub_vec2(CanimVec2 a, CanimVec2 b) {
  return canim_add_vec2(a, canim_negative_vec2(b));
}

CANIM_API CanimNumber canim_dot_vec2(CanimVec2 a, CanimVec2 b) {
  return a.x * b.x + a.y * b.y;
}

CANIM_API CanimVec2 canim_scale_vec2(CanimVec2 a, CanimNumber scaler) {
  return (CanimVec2){.x = a.x * scaler, .y = a.y * scaler};
}

CANIM_API CanimNumber canim_magnitude_vec2(CanimVec2 a) {
  return sqrt(canim_dot_vec2(a, a));
}

CANIM_API CanimVec2 canim_normalize_vec2(CanimVec2 a) {
  return canim_scale_vec2(a, 1 / sqrt(canim_dot_vec2(a, a)));
}

CANIM_API CanimVec2 canim_lerp_vec2(CanimVec2 a, CanimVec2 b, CanimNumber t) {
  return (CanimVec2){.x = canim_lerp(a.x, b.x, t),
                     .y = canim_lerp(a.y, b.y, t)};
}
