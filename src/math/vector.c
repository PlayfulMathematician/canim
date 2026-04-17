// SPDX-License-Identifier: GPL-3.0
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

CANIM_API CanimNumber canim_normal_tri2(CanimTri2 tri) {
  return (tri.points[1].x - tri.points[0].x) *
             (tri.points[2].y - tri.points[0].y) -

         (tri.points[1].y - tri.points[0].y) *
             (tri.points[2].x - tri.points[0].x);
}

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

CANIM_API CanimVec3 canim_normal_tri3(CanimTri3 tri) {
  CanimVec3 edge1 = canim_sub_vec3(tri.points[1], tri.points[0]);
  CanimVec3 edge2 = canim_sub_vec3(tri.points[2], tri.points[0]);
  CanimVec3 normal = canim_cross_vec3(edge1, edge2);
  return canim_normalize_vec3(normal);
}
