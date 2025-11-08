#pragma once
#include <canim/core.h>
#include <canim/gfx.h>
CANIM_API GfxContainer *gfx_load_backend(CanimResult *result,
                                         GfxBackend backend,
                                         const GfxInitInfo *info);
CANIM_API void gfx_unload_backend(CanimResult *result, GfxContainer *gfx);
