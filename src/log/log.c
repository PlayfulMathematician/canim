#include "canim/log.h"
#include "canim/core.h"
#include <stdarg.h>
#include <stdio.h>
CANIM_API void canim_log(CanimLogger *c_log, int line_number, const char *file,
                         CanimLogLevel level, const char *fmt, ...) {
  va_list args;

  va_start(args, fmt);
  FILE *write_to;

  char *status;
  if (level == CANIM_LOG_LEVEL_INFO) {
    write_to = c_log->info_stream;
    status = "INFO";
  }
  if (level == CANIM_LOG_LEVEL_WARNING) {
    write_to = c_log->warning_stream;
    status = "WARNING";
  }
  if (level == CANIM_LOG_LEVEL_ERROR) {
    write_to = c_log->error_stream;
    status = "ERROR";
  }
  fprintf(write_to, "[%s]: %s:%d ", status, file, line_number);
  vfprintf(write_to, fmt, args);
  fprintf(write_to, "\n");
}
