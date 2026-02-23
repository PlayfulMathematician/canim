#include "canim/log.h"
#include "canim/core.h"

CANIM_API void canim_log(CanimLogger *c_log, CanimLog log) {
  if (log.level < c_log->level) {
    return;
  }
  FILE *write_to;

  char *status;
  if (log.level == CANIM_LOG_LEVEL_INFO) {
    write_to = c_log->info_stream;
    status = "INFO";
  }
  if (log.level == CANIM_LOG_LEVEL_WARNING) {
    write_to = c_log->warning_stream;
    status = "WARNING";
  }
  if (log.level == CANIM_LOG_LEVEL_ERROR) {
    write_to = c_log->error_stream;
    status = "ERROR";
  }
  fprintf(write_to, "[%s]: %s:%d %s\n", status, log.file, log.line_number,
          log.reason);
  if (log.note) {
    fprintf(write_to, "\t%s\n", log.reason);
  }
}
