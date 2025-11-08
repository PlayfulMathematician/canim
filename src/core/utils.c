// SPDX-License-Identifier: MIT
#include "canim/core.h"
long read_be_int(const unsigned char *p, int width) {
  long val = 0;
  for (int i = 0; i < width; i++) {
    val = (val << 8) | p[i];
  }
  return val;
}
