// SPDX-License-Identifier: MIT

#include "canim/core.h"
#include "canim/io.h"
#include "canim/log.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static long find_xref(CanimLogger *c_log, FILE *f) {
  long length = canim_get_file_length(c_log, f);
  if (!length) {
    CANIM_LOG_ERROR("Couldn't find XREF, due to lack of file length");
  }

  long starting;
  if (length > BUFFER_SIZE) {
    starting = length - BUFFER_SIZE;
  } else {
    starting = 0;
  }
  long buf_size = length - starting;
  if (fseek(f, starting, SEEK_SET) == -1) {
    CANIM_LOG_ERROR("Couldn't find XREF, fseek failed");
  }
  char buf[BUFFER_SIZE + 1];
  fread(buf, buf_size, 1, f);
  for (int i = 0; i < buf_size; i++) {
    if (buf[i] == 0) {
      buf[i] = 1; // avoids accidentally null terminating it
    }
  }
  buf[buf_size] = '\0';
  return starting + strstr(buf, "startxref") - buf;
}

CANIM_API PdfVersion canim_get_pdf_version(CanimLogger *c_log, FILE *f) {
  long cur = ftell(f);
  fseek(f, 0, SEEK_SET);
  char buf[9];
  fread(buf, 8, 1, f);
  buf[8] = 0;
  PdfVersion version;
  version.minor = (int)buf[7] - '0';
  version.major = (int)buf[5] - '0';
  fseek(f, cur, SEEK_SET);
  return version;
}

PdfXrefTable *get_xref_table(CanimLogger *c_log, FILE *f) {
  long xref_loc = find_xref(c_log, f);
  if (!xref_loc) {
    CANIM_LOG_ERROR("Couldn't get XREF table, we couldn't find the XREF");
  }
  fseek(f, xref_loc, SEEK_SET);
  unsigned int start;
  unsigned int count;
  fscanf(f, "%u %u", &start, &count);
  // TODO: finish this
}
