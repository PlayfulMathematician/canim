#pragma once
#include "canim/core.h"
#include <stdbool.h>
typedef enum {
  CANIM_GFX_NONE = 0,
  CANIM_GFX_GL = 1,
} GfxBackend;
typedef struct GfxDevice GfxDevice;
typedef struct GfxContainer GfxContainer;
typedef struct GfxAPI GfxAPI;
typedef struct {
  bool headless;
  void *native_window;
  int width;
  int height;
} GfxInitInfo;

struct GfxAPI {
  GfxDevice *(*gfx_create_device)(CanimResult *, GfxContainer *,
                                  const GfxInitInfo *);
  void (*gfx_destroy_device)(CanimResult *, GfxContainer *);
};

struct GfxContainer {
  GfxAPI api;
  GfxDevice *impl;
  GfxBackend backend;
};
