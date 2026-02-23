#define CANIM_DEBUG
#include <canim/log.h>
#include <stdio.h>
int main() {
  CanimLogger cl;
  cl.error_stream = stderr;
  cl.warning_stream = stdout;
  cl.info_stream = stdout;
  cl.level = CANIM_LOG_LEVEL_INFO;

  CanimLogger *c_log = &cl;
  canim_log(c_log, (CanimLog){.line_number = __LINE__,
                              .file = __FILE__,
                              .level = CANIM_LOG_LEVEL_ERROR,
                              .note = NULL,
                              .reason = "test"});
  CANIM_LOG_INFO("j");
  CANIM_LOG_INFO_EXT("Hi!", "this is a note");
}
