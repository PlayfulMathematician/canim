#pragma once
#include "canim/core.h"
#include <stdio.h>
typedef enum {
  CANIM_LOG_LEVEL_INFO,
  CANIM_LOG_LEVEL_WARNING,
  CANIM_LOG_LEVEL_ERROR,
} CanimLogLevel;

typedef struct {
  CanimLogLevel level;
  FILE *info_stream;
  FILE *warning_stream;
  FILE *error_stream;
} CanimLogger;

typedef struct {
  int line_number;
  char *file;
  CanimLogLevel level;
  char *reason;
  char *note;
} CanimLog;

CANIM_API void canim_log(CanimLogger *c_log, CanimLog log);
// Note .reason is replaced with .rea##son to avoid macro replacement
//
// https://stackoverflow.com/questions/18167990/suppress-c-macro-variable-substitution
#define CANIM_LOG_INFO(reason)                                                 \
  canim_log(c_log, (CanimLog){.line_number = __LINE__,                         \
                              .file = __FILE__,                                \
                              .level = CANIM_LOG_LEVEL_INFO,                   \
                              .no##te = NULL,                                  \
                              .rea##son = reason})

#define CANIM_LOG_INFO_EXT(reason, note)                                       \
  canim_log(c_log, (CanimLog){.line_number = __LINE__,                         \
                              .file = __FILE__,                                \
                              .level = CANIM_LOG_LEVEL_INFO,                   \
                              .no##te = note,                                  \
                              .rea##son = reason})

#define CANIM_LOG_WARNING_EXT(reason, note)                                    \
  canim_log(c_log, (CanimLog){.line_number = __LINE__,                         \
                              .file = __FILE__,                                \
                              .level = CANIM_LOG_LEVEL_WARNING,                \
                              .no##te = note,                                  \
                              .rea##son = reason})

#define CANIM_LOG_WARNING(reason)                                              \
  canim_log(c_log, (CanimLog){.line_number = __LINE__,                         \
                              .file = __FILE__,                                \
                              .level = CANIM_LOG_LEVEL_WARNING,                \
                              .no##te = NULL,                                  \
                              .rea##son = reason})

#define CANIM_LOG_ERROR_EXT(reason, note)                                      \
  canim_log(c_log, (CanimLog){.line_number = __LINE__,                         \
                              .file = __FILE__,                                \
                              .level = CANIM_LOG_LEVEL_ERROR,                  \
                              .no##te = note,                                  \
                              .rea##son = reason})

#define CANIM_LOG_ERROR(reason)                                                \
  canim_log(c_log, (CanimLog){.line_number = __LINE__,                         \
                              .file = __FILE__,                                \
                              .level = CANIM_LOG_LEVEL_ERROR,                  \
                              .no##te = NULL,                                  \
                              .rea##son = reason})
