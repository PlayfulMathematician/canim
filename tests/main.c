#include <canim/core.h>
#include <canim/gfx.h>
#include <canim/loader.h>
#include <stdio.h>

int main(void) {
  CanimResult result;
  GfxInitInfo info = {
      .width = 800, .height = 600, .headless = false, .native_window = NULL};

  GfxContainer *gfx = gfx_load_backend(&result, CANIM_GFX_GL, &info);
  if (!gfx || IS_AN_ERROR(result)) {
    print_error(result);
    return 1;
  }

  if (!gfx->impl) {
    gfx_unload_backend(&result, gfx);
    return 1;
  }

  gfx_unload_backend(&result, gfx);

  return 0;
}
