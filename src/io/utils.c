// SPDX-License-Identifier: MIT
#include "canim/core.h"
#include "canim/io.h"
#include <stdio.h>
CANIM_API long canim_get_file_length(CanimResult *c_result, FILE *f) {
  long prev = ftell(f);
  if (prev == -1) {
    CANIM_RESULT_FATAL(CANIM_RESULT_CODE_FILE);

    return 0;
  }
  if (fseek(f, 0, SEEK_END) == -1) {
    fseek(f, prev, SEEK_SET);
    CANIM_RESULT_FATAL(CANIM_RESULT_CODE_FILE);

    return 0;
  }
  long length = ftell(f);
  if (length == -1) {
    CANIM_RESULT_FATAL(CANIM_RESULT_CODE_FILE);
    return 0;
  }
  fseek(f, prev, SEEK_SET);
  return length;
}
