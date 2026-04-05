// SPDX-License-Identifier: GPL-3.0
#include <canim/io.h>
#include <stdint.h>

#include <canim/gfx.h>
#include <canim/loader.h>
#include <canim/log.h>

int main() {
  CANIM_CREATE_LOGGER(CANIM_LOG_LEVEL_INFO);
  CanimGfxInitInfo init = {
      .headless = false, .width = 1000, .height = 1000, .native_window = NULL};

  CanimGfxContainer *container =
      canim_gfx_load_backend(c_log, CANIM_GFX_GL, &init);
  container->api.gfx_setup_shaders(c_log, container);
  CanimScreenBuffer buf = canim_allocate_screen_buffer(
      c_log, (uint64_t)init.width, (uint64_t)init.height);
  CanimPipe pipe =
      canim_create_ffmpeg_pipe(c_log, (uint64_t)init.width,
                               (uint64_t)init.height, (uint64_t)60, "test.mp4");
  bool running = false;
  int tick = 0;

  float vertices[] = {
      // face 0
      0.0f,
      0.5f,
      0.2f,
      0.0f,
      0.5774f,
      0.8165f,
      0.5f,
      -0.5f,
      0.5f,
      0.0f,
      0.5774f,
      0.8165f,
      -0.5f,
      -0.5f,
      0.5f,
      0.0f,
      0.5774f,
      0.8165f,
      // face 1
      0.0f,
      0.5f,
      0.2f,
      -0.8165f,
      0.5774f,
      -0.4082f,
      -0.5f,
      -0.5f,
      0.5f,
      -0.8165f,
      0.5774f,
      -0.4082f,
      0.0f,
      -0.5f,
      -0.5f,
      -0.8165f,
      0.5774f,
      -0.4082f,
      // face 2
      0.0f,
      0.5f,
      0.2f,
      0.8165f,
      0.5774f,
      -0.4082f,
      0.0f,
      -0.5f,
      -0.5f,
      0.8165f,
      0.5774f,
      -0.4082f,
      0.5f,
      -0.5f,
      0.5f,
      0.8165f,
      0.5774f,
      -0.4082f,
      // face 3
      0.5f,
      -0.5f,
      0.5f,
      0.0f,
      -1.0f,
      0.0f,
      0.0f,
      -0.5f,
      -0.5f,
      0.0f,
      -1.0f,
      0.0f,
      -0.5f,
      -0.5f,
      0.5f,
      0.0f,
      -1.0f,
      0.0f,
  };

  while (tick < 120) {
    container->api.gfx_should_close(c_log, container, &running);
    container->api.gfx_draw_mesh(c_log, container, vertices, sizeof(vertices));
    container->api.gfx_swap_buffers(c_log, container);
    container->api.gfx_save_screen(c_log, container, buf);
    canim_pipe_into_ffmpeg(c_log, buf, pipe);
    tick++;
  }
  canim_close_pipe(pipe);
  container->api.gfx_destroy_device(c_log, container);
  canim_gfx_unload_backend(c_log, container);
}
