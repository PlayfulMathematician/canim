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

// @def canim_log
// @brief This logs stuff
// @param c_log The logger in question
// @param line_number The line number of the log
// @param file The file the log is occuring
// @param level The severity of the log
// @param fmt A string format
// @param ... The other string format stuff
CANIM_API void canim_log(CanimLogger *c_log, int line_number, const char *file,
                         CanimLogLevel level, const char *fmt, ...);

// @def CANIM_LOG
// @brief This macro is a simple wrapper around canim_log,
// @param level This is the level of the  log
// @param ... Format related information
#define CANIM_LOG(level, ...)                                                  \
  canim_log(c_log, __LINE__, __FILE__, level, __VA_ARGS__)
// @def CANIM_LOG_INFO
// @brief This macro logs info
#define CANIM_LOG_INFO(...) CANIM_LOG(CANIM_LOG_LEVEL_INFO, __VA_ARGS__)

// @def CANIM_LOG_WARNING
// @brief This macro logs warnings
#define CANIM_LOG_WARNING(...) CANIM_LOG(CANIM_LOG_LEVEL_WARNING, __VA_ARGS__)

// @def CANIM_LOG_ERROR
// @brief This macro logs errors
#define CANIM_LOG_ERROR(...) CANIM_LOG(CANIM_LOG_LEVEL_ERROR, __VA_ARGS__)

// @def CANIM_CREATE_LOGGER
// @brief This is the level of the logger
// @param level This is the level of the logger
#define CANIM_CREATE_LOGGER(level)                                             \
  CanimLogger clog;                                                            \
  clog.lev##el = level;                                                        \
  clog.info_stream = stdout;                                                   \
  clog.error_stream = stdout;                                                  \
  clog.warning_stream = stderr;                                                \
  CanimLogger *c_log = &clog
