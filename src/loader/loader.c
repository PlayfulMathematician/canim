// SPDX-License-Identifier: AGPL-3.0
#include "canim/loader.h"
#include "canim/core.h"
#include "canim/gfx.h"
#include <stdlib.h>
#ifdef CANIM_POSIX
#include <dlfcn.h>
#define LIB_HANDLE void *
#define LIB_LOAD(name) dlopen(name, RTLD_NOW | RTLD_LOCAL)
#define LIB_SYM(h, sym) dlsym(h, sym)
#define LIB_CLOSE(h) dlclose(h)
#endif
#ifdef CANIM_PLATFORM_LINUX
#define LIB_EXT ".so"
#endif
#ifdef CANIM_PLATFORM_MAC
#define LIB_EXT ".dylib"
#endif
#ifdef CANIM_PLATFORM_WINDOWS
#include <windows.h>
#define LIB_HANDLE HMODULE
#define LIB_LOAD(name) LoadLibraryA(name)
#define LIB_SYM(h, sym) GetProcAddress(h, sym)
#define LIB_CLOSE(h) FreeLibrary(h)
#define LIB_EXT ".dll"
#endif
const char *gfx_backend_libname(GfxBackend backend) {
  switch (backend) {
  case CANIM_GFX_GL:
    return "libcanim_gl" LIB_EXT;
  default:
    return NULL;
  }
}
CANIM_API GfxContainer *canim_gfx_load_backend(CanimResult *result,
                                               GfxBackend backend,
                                               const GfxInitInfo *info) {
  const char *libname = gfx_backend_libname(backend);
  LIB_HANDLE handle = LIB_LOAD(libname);
  const GfxAPI *const *entry =
      (const GfxAPI *const *)LIB_SYM(handle, "GFX_API_ENTRY");
  GfxContainer *gfx = calloc(1, sizeof(*gfx));
  const GfxAPI *api = *entry;
  gfx->api = *api;
  gfx->impl = NULL;
  gfx->backend = backend;
  GfxDevice *dev = gfx->api.gfx_create_device(result, gfx, info);
  if (IS_AN_ERROR(*result)) {
    return NULL;
  }
  gfx->handle = (void *)handle;
  gfx->impl = dev;
  *result = SUCCESS;
  return gfx;
}

CANIM_API void canim_gfx_unload_backend(CanimResult *result,
                                        GfxContainer *gfx) {
  LIB_CLOSE((LIB_HANDLE)gfx->handle);
  *result = SUCCESS;
}
