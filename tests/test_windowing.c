#define CANIM_DEBUG

#include "canim/canim.h"
#include "canim/core.h"
#include "canim/gfx.h"
#include "canim/loader.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <stdio.h>
#include <unistd.h>
int main() {
  setvbuf(stdout, NULL, _IONBF, 0);
  CanimResult _;
  CanimResult *c_result = &_;
  CANIM_RESULT_SUCCESS();
  CanimGfxInitInfo init = {
      .headless = false, .width = 100, .height = 100, .native_window = NULL};

  CanimGfxContainer *container =
      canim_gfx_load_backend(c_result, CANIM_GFX_GL, &init);

  if (canim_is_error(c_result)) {
    abort();
  }
  bool running = true;

  while (running) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT ||
          (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
        running = false;
      }
    }
    container->api.gfx_swap_buffers(c_result, container);

    SDL_Delay(16);
  }
  container->api.gfx_destroy_device(c_result, container);

  canim_gfx_unload_backend(c_result, container);
}
