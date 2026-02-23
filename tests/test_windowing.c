#define CANIM_DEBUG

#include "canim/log.h"

#include "canim/gfx.h"
#include "canim/loader.h"

#include <stdio.h>
int main() {
  setvbuf(stdout, NULL, _IONBF, 0);

  CANIM_CREATE_LOGGER(CANIM_LOG_LEVEL_INFO);
  CanimGfxInitInfo init = {
      .headless = false, .width = 100, .height = 100, .native_window = NULL};

  CanimGfxContainer *container =
      canim_gfx_load_backend(c_log, CANIM_GFX_GL, &init);

  bool running = true;

  while (running) {
    container->api.gfx_should_close(c_log, container, &running);
    container->api.gfx_swap_buffers(c_log, container);
  }
  container->api.gfx_destroy_device(c_log, container);
  canim_gfx_unload_backend(c_log, container);
}
