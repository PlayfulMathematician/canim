#include "canim/core.h"
#include "canim/io.h"
#include <stdio.h>
static long get_length(CanimResult *result, FILE *f) {
  long prev = ftell(f);
  if (fseek(f, 0, SEEK_END) == -1) {
    fseek(f, prev, SEEK_SET);
    *result = FSEEK_FAILURE;
    return 0;
  }
  long length = ftell(f);
  fseek(f, prev, SEEK_SET);
  return length;
}
