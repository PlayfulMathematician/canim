
#define CANIM_DEBUG
#include "canim/io.h"
#include <stdint.h>

#include <canim/log.h>

#include <canim/gfx.h>
#include <canim/loader.h>

#include <stdio.h>
int main() {
  setvbuf(stdout, NULL, _IONBF, 0);

  CANIM_CREATE_LOGGER(CANIM_LOG_LEVEL_INFO);
  CanimGfxInitInfo init = {
      .headless = false, .width = 100, .height = 100, .native_window = NULL};

  CanimGfxContainer *container =
      canim_gfx_load_backend(c_log, CANIM_GFX_GL, &init);
  CanimScreenBuffer buf =
      canim_allocate_screen_buffer(c_log, (uint64_t)100, (uint64_t)100);
  CanimPipe pipe = canim_create_ffmpeg_pipe(c_log, (uint64_t)100, (uint64_t)100,
                                            (uint64_t)100, "test.mp4");
  bool running = true;
  int tick = 0;
  while (tick < 60) {
    container->api.gfx_should_close(c_log, container, &running);

    container->api.gfx_swap_buffers(c_log, container);
    container->api.gfx_save_screen(c_log, container, buf);
    canim_pipe_into_ffmpeg(c_log, buf, pipe);
    tick++;
  }
  container->api.gfx_destroy_device(c_log, container);
  canim_gfx_unload_backend(c_log, container);
}
