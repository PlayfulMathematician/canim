// SPDX-License-Identifier: GPL-3.0
#pragma once
#include "canim/core.h"
#include "canim/log.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
typedef struct {
  uint8_t major;
  uint8_t minor;
} PdfVersion;
// glPixelStorei(GL_PACK_ALIGNMENT, 1);
//  glReadPixels(0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, rgb);
typedef FILE *CanimPipe;
typedef struct {
  CanimU64 width;
  CanimU64 height;
  CanimByte *data;
} CanimScreenBuffer;
typedef struct {
  uint32_t offset;
  uint16_t gen;
  bool in_use;
} PdfXrefEntry;

typedef struct {
  uint32_t size;
  PdfXrefEntry *entries;
} PdfXrefTable;
/// @brief This computes the length of a given file in Canim
/// @param[out] c_log A logger
/// @param f Pointer to the file
/// @return The length of the file
CANIM_API long canim_get_file_length(CanimLogger *c_log, FILE *f);
CANIM_API unsigned char *canim_decompress_flate(CanimLogger *c_log,
                                                unsigned char *input,
                                                size_t input_len,
                                                size_t *output_len);
CANIM_API PdfVersion canim_get_pdf_version(CanimLogger *c_log, FILE *f);

CANIM_API CanimScreenBuffer canim_allocate_screen_buffer(CanimLogger *c_log,
                                                         CanimU64 w,
                                                         CanimU64 h);
CANIM_API CanimPipe canim_create_ffmpeg_pipe(CanimLogger *c_log, CanimU64 w,
                                             CanimU64 h, CanimU64 fps,
                                             const char *out);

CANIM_API bool canim_pipe_into_ffmpeg(CanimLogger *c_log, CanimScreenBuffer buf,
                                      CanimPipe pipe);

CANIM_API void canim_close_pipe(CanimPipe pipe);
