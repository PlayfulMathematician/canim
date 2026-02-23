// SPDX-License-Identifier: MIT
#include "canim/core.h"
#include "canim/io.h"
#include "canim/log.h"
#include <stdio.h>
CANIM_API long canim_get_file_length(CanimLogger *c_log, FILE *f) {
  long prev = ftell(f);
  if (prev == -1) {
    CANIM_LOG_WARNING("When trying to find file length, ftell failed");
  }
  if (fseek(f, 0, SEEK_END) == -1) {
    fseek(f, prev, SEEK_SET);

    CANIM_LOG_ERROR("When trying to find file length, fseek failed");

    return 0;
  }
  long length = ftell(f);
  if (length == -1) {

    CANIM_LOG_ERROR("When trying to find file length, fseek failed");

    return 0;
  }
  fseek(f, prev, SEEK_SET);
  return length;
}
