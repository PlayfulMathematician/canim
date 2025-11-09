#include <canim/core.h>
#include <canim/gfx.h>
#include <canim/loader.h>
#include <stdio.h>

int main(void) {
  CanimResult result;
  GfxInitInfo info = {
      .width = 800, .height = 600, .headless = false, .native_window = NULL};

  printf("🔍 Loading OpenGL backend...\n");
  GfxContainer *gfx = gfx_load_backend(&result, CANIM_GFX_GL, &info);
  if (!gfx || IS_AN_ERROR(result)) {
    print_error(result);
    return 1;
  }

  printf("✅ Backend loaded: libgl.so\n");
  printf("🎨 Creating and initializing device...\n");

  if (!gfx->impl) {
    printf("❌ Device creation failed.\n");
    gfx_unload_backend(&result, gfx);
    return 1;
  }

  printf("🌈 Device successfully created.\n");

  // Optionally, run a dummy render call
  printf("🧹 Cleaning up...\n");
  gfx_unload_backend(&result, gfx);

  printf("✅ Test complete.\n");
  return 0;
}
