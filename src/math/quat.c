#include "canim/math.h"
#include <math.h>
CANIM_API CanimQuat canim_quat_identity(void) {
  return (CanimQuat){0, 0, 0, 1};
}

CANIM_API CanimQuat canim_quat_add(CanimQuat a, CanimQuat b) {
  return (CanimQuat){a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
}

CANIM_API CanimQuat canim_quat_sub(CanimQuat a, CanimQuat b) {
  return (CanimQuat){a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
}

CANIM_API CanimQuat canim_quat_scale(CanimQuat q, CanimNumber s) {
  return (CanimQuat){q.x * s, q.y * s, q.z * s, q.w * s};
}

CANIM_API CanimNumber canim_quat_dot(CanimQuat a, CanimQuat b) {
  return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

CANIM_API CanimNumber canim_quat_magnitude(CanimQuat q) {
  return sqrt(canim_quat_dot(q, q));
}

CANIM_API CanimQuat canim_quat_normalize(CanimQuat q) {
  CanimNumber mag = canim_quat_magnitude(q);

  if (mag == 0) {
    return canim_quat_identity();
  }

  return canim_quat_scale(q, 1 / mag);
}

CANIM_API CanimQuat canim_quat_conjugate(CanimQuat q) {
  return (CanimQuat){-q.x, -q.y, -q.z, q.w};
}

CANIM_API CanimQuat canim_quat_inverse(CanimQuat q) {
  CanimNumber mag_sq = canim_quat_dot(q, q);

  if (mag_sq == 0) {
    return canim_quat_identity();
  }

  return canim_quat_scale(canim_quat_conjugate(q), 1 / mag_sq);
}

CANIM_API CanimQuat canim_quat_mul(CanimQuat a, CanimQuat b) {
  return (CanimQuat){a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
                     a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x,
                     a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w,
                     a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z};
}
