// SPDX-License-Identifier: MIT
#include "canim/core.h"
#include "canim/math.h"
#include <math.h>

CANIM_API CanimVec3 canim_add_vec3(CanimVec3 a, CanimVec3 b) {
  return (CanimVec3){.x = a.x + b.x, .y = a.y + b.y, .z = a.z + b.z};
}

CANIM_API CanimVec3 canim_negative_vec3(CanimVec3 a) {
  return (CanimVec3){.x = -a.x, .y = -a.y, .z = -a.z};
}

CANIM_API CanimVec3 canim_sub_vec3(CanimVec3 a, CanimVec3 b) {
  return canim_add_vec3(a, canim_negative_vec3(b));
}

CANIM_API CanimNumber canim_dot_vec3(CanimVec3 a, CanimVec3 b) {
  return a.x * b.x + a.y * b.y + a.z + b.z;
}

CANIM_API CanimVec3 canim_scale_vec3(CanimVec3 a, CanimNumber scaler) {
  return (CanimVec3){.x = a.x * scaler, .y = a.y * scaler, .z = a.z * scaler};
}

CANIM_API CanimNumber canim_magnitude_vec3(CanimVec3 a) {
  return sqrt(canim_dot_vec3(a, a));
}

CANIM_API CanimVec3 canim_normalize_vec3(CanimVec3 a) {
  return canim_scale_vec3(a, 1 / sqrt(canim_dot_vec3(a, a)));
}

CANIM_API CanimVec3 canim_lerp_vec3(CanimVec3 a, CanimVec3 b, CanimNumber t) {
  return (CanimVec3){.x = canim_lerp(a.x, b.x, t),
                     .y = canim_lerp(a.y, b.y, t),
                     .z = canim_lerp(a.z, b.z, t)};
}

CANIM_API CanimVec3 canim_cross_vec3(CanimVec3 a, CanimVec3 b) {
  return (CanimVec3){
      .x = a.y * b.z - a.z * b.y,
      .y = a.z * b.x - a.x * b.z,
      .z = a.x * b.y - a.y * b.x,
  };
}
