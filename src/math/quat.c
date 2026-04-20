#include "canim/math.h"
#include <math.h>

CANIM_API CanimQuat canim_quat_identity(void) {
  return (CanimQuat){
      .w = 1.0f,
      .x = 0.0f,
      .y = 0.0f,
      .z = 0.0f,
  };
}

CANIM_API CanimQuat canim_quat_normalize(CanimQuat q) {
  CanimNumber mag = sqrtf(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);
  if (mag == 0.0f) {
    return canim_quat_identity();
  }

  return (CanimQuat){
      .w = q.w / mag,
      .x = q.x / mag,
      .y = q.y / mag,
      .z = q.z / mag,
  };
}

CANIM_API CanimQuat canim_quat_conjugate(CanimQuat q) {
  return (CanimQuat){
      .w = q.w,
      .x = -q.x,
      .y = -q.y,
      .z = -q.z,
  };
}

CANIM_API CanimQuat canim_quat_mul(CanimQuat a, CanimQuat b) {
  return (CanimQuat){
      .x = a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
      .y = a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x,
      .z = a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w,
      .w = a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z,
  };
}

CANIM_API CanimQuat canim_quat_from_axis_angle(CanimVec3 axis,
                                               CanimNumber angle) {
  if (axis.x == 0.0 && axis.y == 0.0 && axis.z == 0.0) {
    return canim_quat_identity();
  }
  CanimNumber half = angle * 0.5f;
  CanimNumber s = sinf(half);
  CanimNumber c = cosf(half);
  return (CanimQuat){
      .x = axis.x * s,
      .y = axis.y * s,
      .z = axis.z * s,
      .w = c,
  };
}

CANIM_API CanimVec3 canim_quat_rotate_vec3(CanimQuat q, CanimVec3 v) {
  q = canim_quat_normalize(q);
  CanimQuat vq = {
      .x = v.x,
      .y = v.y,
      .z = v.z,
      .w = 0.0f,
  };
  CanimQuat q_conj = canim_quat_conjugate(q);
  CanimQuat result = canim_quat_mul(canim_quat_mul(q, vq), q_conj);
  return (CanimVec3){
      .x = result.x,
      .y = result.y,
      .z = result.z,
  };
}
