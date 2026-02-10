// SPDX-License-Identifier: MIT
#include "canim/core.h"

CANIM_API bool canim_is_error(CanimResult *c_result) {
  return c_result->status != CANIM_RESULT_STATUS_SUCCESS &&
         c_result->status != CANIM_RESULT_STATUS_DEPRECATED;
}

CANIM_API void print_error(CanimResult *c_result) { return; }
