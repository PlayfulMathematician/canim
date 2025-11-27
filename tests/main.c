#include <SDL2/SDL.h>
#include <canim/canim.h>
#include <unistd.h>

int main(void) {
  CanimResult result;
  GfxInitInfo info = {
      .width = 800, .height = 600, .headless = false, .native_window = NULL};

  GfxContainer *gfx = gfx_load_backend(&result, CANIM_GFX_GL, &info);
  if (!gfx || IS_AN_ERROR(result)) {
    print_error(result);
    return 1;
  }
  Uint32 start = SDL_GetTicks();
  while (SDL_GetTicks() - start < 3000) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      // no handling needed
    }

    SDL_Delay(16);
  }
  if (!gfx->impl) {
    gfx_unload_backend(&result, gfx);
    return 1;
  }

  gfx_unload_backend(&result, gfx);
  return 0;
}
