#pragma once
#include "canim/core.h"
#include <stdio.h>

// @enum CanimLogLevel
// @brief This is the type, and level of a certain log
typedef enum {
  // @def CANIM_LOG_LEVEL_INFO
  // @brief This is for info logs
  CANIM_LOG_LEVEL_INFO,

  // @def CANIM_LOG_LEVEL_WARNING
  // @brief This is for warning logs
  CANIM_LOG_LEVEL_WARNING,

  // @def CANIM_LOG_LEVEL_ERROR
  // @brief This is for error logs
  CANIM_LOG_LEVEL_ERROR,

  // @def CANIM_LOG_LEVEL_NONE
  // @brief This is used to signify that nothing should be logged
  CANIM_LOG_LEVEL_NONE
} CanimLogLevel;

// @struct CanimLogger
// @brief This stores a Logger
typedef struct {
  CanimLogLevel level;  ///< This is the level for which logs are accepted
  FILE *info_stream;    ///< This is where info logs are printed (recommended is
                        ///< stdout)
  FILE *warning_stream; ///< This is where warning logs are printed (recommended
                        ///< is stdout)
  FILE *error_stream; ///< This is where error logs are printed (recommended is
                      ///< stderr)
} CanimLogger;

// @struct CanimLog
// @brief This stores an individual log
typedef struct {
  int line_number;     ///< What line number is this log?
  char *file;          ///< What file is this log made from
  CanimLogLevel level; ///< What level is this log?
  char *reason;        ///< The contents of this log
  char *note;          ///< Other stuff
} CanimLog;

CANIM_API void canim_log(CanimLogger *c_log, CanimLog log);
// Note .reason is replaced with .rea##son to avoid macro replacement
//
// https://stackoverflow.com/questions/18167990/suppress-c-macro-variable-substitution

// TODO Document this
#define CANIM_LOG_INFO(reason)                                                 \
  canim_log(c_log, (CanimLog){.line_number = __LINE__,                         \
                              .file = __FILE__,                                \
                              .level = CANIM_LOG_LEVEL_INFO,                   \
                              .no##te = NULL,                                  \
                              .rea##son = reason})

// TODO Document this
#define CANIM_LOG_INFO_EXT(reason, note)                                       \
  canim_log(c_log, (CanimLog){.line_number = __LINE__,                         \
                              .file = __FILE__,                                \
                              .level = CANIM_LOG_LEVEL_INFO,                   \
                              .no##te = note,                                  \
                              .rea##son = reason})

// TODO Document this
#define CANIM_LOG_WARNING_EXT(reason, note)                                    \
  canim_log(c_log, (CanimLog){.line_number = __LINE__,                         \
                              .file = __FILE__,                                \
                              .level = CANIM_LOG_LEVEL_WARNING,                \
                              .no##te = note,                                  \
                              .rea##son = reason})

// TODO Document this
#define CANIM_LOG_WARNING(reason)                                              \
  canim_log(c_log, (CanimLog){.line_number = __LINE__,                         \
                              .file = __FILE__,                                \
                              .level = CANIM_LOG_LEVEL_WARNING,                \
                              .no##te = NULL,                                  \
                              .rea##son = reason})

// TODO Document this
#define CANIM_LOG_ERROR_EXT(reason, note)                                      \
  canim_log(c_log, (CanimLog){.line_number = __LINE__,                         \
                              .file = __FILE__,                                \
                              .level = CANIM_LOG_LEVEL_ERROR,                  \
                              .no##te = note,                                  \
                              .rea##son = reason})

// TODO Document this
#define CANIM_LOG_ERROR(reason)                                                \
  canim_log(c_log, (CanimLog){.line_number = __LINE__,                         \
                              .file = __FILE__,                                \
                              .level = CANIM_LOG_LEVEL_ERROR,                  \
                              .no##te = NULL,                                  \
                              .rea##son = reason})

// TODO Document this
#define CANIM_CREATE_LOGGER(level)                                             \
  CanimLogger clog;                                                            \
  clog.lev##el = level;                                                        \
  clog.info_stream = stdout;                                                   \
  clog.error_stream = stdout;                                                  \
  clog.warning_stream = stderr;                                                \
                                                                               \
  CanimLogger *c_log = &clog
