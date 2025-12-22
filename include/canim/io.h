#include "canim/core.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
/// @brief This computes the length of a given file in Canim
/// @param[out] result A status code
/// @param f Pointer to the file
/// @return The length of the file
static long get_length(CanimResult *result, FILE *f);

/// @brief Find XRef
static long find_xref(CanimResult *result, FILE *f);

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
