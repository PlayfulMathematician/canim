// SPDX-License-Identifier: GPL-3.0
#pragma once
#include "canim/core.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
typedef struct {
  uint8_t major;
  uint8_t minor;
} PdfVersion;

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
/// @param[out] result A status code
/// @param f Pointer to the file
/// @return The length of the file
CANIM_API long canim_get_file_length(CanimResult *result, FILE *f);
CANIM_API unsigned char *canim_decompress_flate(CanimResult *result,
                                                unsigned char *input,
                                                size_t input_len,
                                                size_t *output_len);
CANIM_API PdfVersion canim_get_pdf_version(CanimResult *result, FILE *f);
