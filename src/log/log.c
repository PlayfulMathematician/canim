#include "canim/log.h"
#include "canim/core.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
CANIM_API void canim_log(CanimLogger *c_log, int line_number, const char *file,
                         CanimLogLevel level, const char *fmt, ...) {
  if (level < c_log->level) {
    return;
  }
  va_list args;

  va_start(args, fmt);
  FILE *write_to;

  char *status;
  switch (level) {
  case CANIM_LOG_LEVEL_INFO:
    write_to = c_log->info_stream;
    status = "INFO";
    break;
  case CANIM_LOG_LEVEL_WARNING:
    write_to = c_log->warning_stream;
    status = "WARNING";
    break;
  case CANIM_LOG_LEVEL_ERROR:
    write_to = c_log->error_stream;
    status = "ERROR";
    break;
  default:
    abort();
  }
  fprintf(write_to, "[%s]: %s:%d ", status, file, line_number);
  vfprintf(write_to, fmt, args);
  va_end(args);
  fprintf(write_to, "\n");
}
