// SPDX-License-Identifier: GPL-3.0
// @file log.h
// @brief This header handles logging
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
  // @def level
  // @brief This is the log level
  CanimLogLevel level;

  // @def info_stream
  // @brief This is the info stream where info is printed
  FILE *info_stream;

  // @def warning_stream
  // @brief This is the warning stream where warnings are printed
  FILE *warning_stream;

  // @def error_stream
  // @brief This is the stream where errors are printed
  FILE *error_stream;
} CanimLogger;

// @struct CanimLog
// @brief This stores an individual log
typedef struct {
  // @def line_number
  // @brief The line number of the log
  int line_number;

  // @def file
  // @brief The file of the log
  char *file;

  // @def level
  // @brief The severity of the log
  CanimLogLevel level;

  // @def reason
  // @brief The reason for this log
  char *reason;

  // @def note
  // @brief If there exists other information produced from stuff like errno,
  // this variable will store it
  char *note;
} CanimLog;

// @def canim_log
// @brief This is the function that logs something
// @param c_log The Logger
// @param log The log
CANIM_API void canim_log(CanimLogger *c_log, CanimLog log);

// @def CANIM_LOG
// @brief This macro is a simple wrapper around canim_log,
// @param level This is the level of the  log
// @param reason This is the reason for the log
// @param ... An optional note
#define CANIM_LOG(level, reason, ...)                                          \
  canim_log(c_log,                                                             \
            (CanimLog){.line_number = __LINE__,                                \
                       .file = __FILE__,                                       \
                       .lev##el = level,                                       \
                       .rea##son = reason __VA_OPT__(, .note =) __VA_ARGS__})

// @def CANIM_LOG_INFO
// @brief This macro logs info
#define CANIM_LOG_INFO(...) CANIM_LOG(CANIM_LOG_LEVEL_INFO, __VA_ARGS__)

// @def CANIM_LOG_WARNING
// @brief This macro logs warnings
#define CANIM_LOG_WARNING(...) CANIM_LOG(CANIM_LOG_LEVEL_WARNING, __VA_ARGS__)

// @def CANIM_LOG_ERROR
// @brief This macro logs errors
#define CANIM_LOG_ERROR(...) CANIM_LOG(CANIM_LOG_LEVEL_ERROR, __VA_ARGS__)

// @def CANIM_LOG_INFO_EXT
// @deprecated
#define CANIM_LOG_INFO_EXT CANIM_LOG_INFO

// @def CANIM_LOG_WARNING_EXT
// @deprecated
#define CANIM_LOG_WARNING_EXT CANIM_LOG_WARNING

// @def CANIM_LOG_ERROR_EXT
// @deprecated
#define CANIM_LOG_ERROR_EXT CANIM_LOG_ERROR

// @def CANIM_CREATE_LOGGER
// @brief This is the level of the logger
// @param level This is the level of the logger
#define CANIM_CREATE_LOGGER(level)                                             \
  CanimLogger clog;                                                            \
  clog.lev##el = level;                                                        \
  clog.info_stream = stdout;                                                   \
  clog.error_stream = stdout;                                                  \
  clog.warning_stream = stderr;                                                \
                                                                               \
  CanimLogger *c_log = &clog
