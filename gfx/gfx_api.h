#ifndef GFX_API_H
#define GFX_API_H
#include "../shared.h"
#include <stdbool.h>
typedef struct GfxDevice GfxDevice;
typedef struct Triangulation Triangulation;
typedef struct {
  bool headless;
  void *native_window;
  int width;
  int height;
} GfxInitInfo;

CANIM_API GfxDevice *gfx_create_device(CanimResult *result,
                                       const GfxInitInfo *info);
CANIM_API void gfx_destroy_device(CanimResult *result, GfxDevice *device);
#endif
