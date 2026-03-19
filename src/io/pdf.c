// SPDX-License-Identifier: GPL-3.0

#include "canim/core.h"
#include "canim/io.h"
#include "canim/log.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
CANIM_API PdfVersion canim_get_pdf_version(CanimLogger *c_log, FILE *f) {
  long cur = ftell(f);
  fseek(f, 0, SEEK_SET);
  char buf[9];
  fread(buf, 8, 1, f);
  buf[8] = 0;
  PdfVersion version;
  version.minor = buf[7] - '0';
  version.major = buf[5] - '0';
  fseek(f, cur, SEEK_SET);
  return version;
}
