// SPDX-License-Identifier: AGPL-3.0
#include "zlib.h"
#include "canim/core.h"
#include "canim/io.h"
#include <stdbool.h>
#include <stdlib.h>
CANIM_API unsigned char *canim_decompress_flate(CanimResult *result,
                                                unsigned char *input,
                                                size_t input_len,
                                                size_t *output_len) {
  unsigned char *buf;
  buf = malloc(8 * input_len);
  if (buf == NULL) {
    *result = MALLOC_FAIL;
    return NULL;
  }
  z_stream strm;
  strm.avail_in = input_len;
  strm.avail_out = input_len * 8;
  strm.next_in = input;
  strm.next_out = buf;
  strm.opaque = NULL;
  strm.zalloc = NULL;
  strm.zfree = NULL;
  inflateInit(&strm);
  inflate(&strm, Z_FINISH);
  inflateEnd(&strm);
  *output_len = strm.total_out;
  *result = SUCCESS;
  return buf;
}
