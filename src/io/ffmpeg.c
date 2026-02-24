#include "canim/io.h"
#include "canim/log.h"
#include <errno.h>
#include <string.h>
CANIM_API CanimPipe canim_create_ffmpeg_pipe(CanimLogger *c_log, CanimU64 w,
                                             CanimU64 h, CanimU64 fps,
                                             const char *out) {
  char cmd[1024];
  snprintf(
      cmd, sizeof(cmd),
      "ffmpeg -y -f rawvideo -pixel_format rgb24 -video_size %dx%d -framerate "
      "%d -i - "
      "-vf vflip -c:v libx264 -preset veryfast -crf 18 -pix_fmt yuv420p \"%s\"",
      (int)w, (int)h, (int)fps, out);

  CanimPipe pipef = popen(cmd, "w");
  if (!pipef) {
    CANIM_LOG_ERROR("Creating the ffmpeg pipe failed");
    CANIM_LOG_ERROR(strerror(errno));
  }

  return pipef;
}

CANIM_API bool canim_pipe_into_ffmpeg(CanimLogger *c_log, CanimScreenBuffer buf,
                                      CanimPipe pipe) {
  fwrite(buf.data, 1, buf.width * buf.height * 3, pipe);
  return true;
}

CANIM_API void canim_close_pipe(CanimPipe pipe) { pclose(pipe); }
