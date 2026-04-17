// SPDX-License-Identifier: GPL-3.0
#include "canim/core.h"
#include "canim/math.h"

CANIM_API CanimMat4 canim_translation_matrix(CanimVec3 v) {
  return (CanimMat4){.m = {
                         {1, 0, 0, v.x},
                         {0, 1, 0, v.y},
                         {0, 0, 1, v.z},
                         {0, 0, 0, 1},
                     }};
};
