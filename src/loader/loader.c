// SPDX-License-Identifier: MIT

#include "canim/loader.h"
#include "canim/core.h"
#include "canim/gfx.h"
#include "canim/log.h"
#include <dlfcn.h>
#include <stdlib.h>
#ifdef CANIM_PLATFORM_LINUX
#define LIB_EXT ".so"
#endif
#ifdef CANIM_PLATFORM_MACOS
#define LIB_EXT ".dylib"
#endif

const char *gfx_backend_libname(CanimGfxBackend backend) {
  switch (backend) {
  case CANIM_GFX_GL:
    return "libcanim_gl" LIB_EXT;
  default:
    return NULL;
  }
}
CANIM_API CanimGfxContainer *
canim_gfx_load_backend(CanimLogger *c_log, CanimGfxBackend backend,
                       const CanimGfxInitInfo *info) {
#ifdef CANIM_POSIX
  dlerror();
#endif
  const char *libname = gfx_backend_libname(backend);
  void *handle = dlopen(libname, RTLD_NOW | RTLD_LOCAL);
  const CanimGfxAPI *const *entry =
      (const CanimGfxAPI *const *)dlsym(handle, "GFX_API_ENTRY");
#ifdef CANIM_POSIX
  char *err = dlerror();
  if (err != NULL) {
    CANIM_LOG_ERROR_EXT("Loading external libraries failed", err);
    dlclose(handle);
    return NULL;
  }
#endif
  CanimGfxContainer *gfx = calloc(1, sizeof(*gfx));
  if (!gfx) {
    dlclose(handle);

    CANIM_LOG_ERROR("Allocating a graphics container failed");
    return NULL;
  }
  const CanimGfxAPI *api = *entry;
  gfx->api = *api;
  gfx->impl = NULL;
  gfx->backend = backend;
  CanimGfxDevice *dev = gfx->api.gfx_create_device(c_log, gfx, info);

  if (!dev) {
    CANIM_LOG_ERROR("Creating a graphics device failed!");
    return NULL;
  }
  gfx->handle = (void *)handle;
  gfx->impl = dev;
  return gfx;
}

CANIM_API void canim_gfx_unload_backend(CanimLogger *c_log,
                                        CanimGfxContainer *gfx) {
  dlclose(gfx->handle);
}
