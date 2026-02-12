// SPDX-License-Identifier: MIT

#include "canim/loader.h"
#include "canim/core.h"
#include "canim/gfx.h"
#include <stdlib.h>
#ifdef CANIM_POSIX
#include <dlfcn.h>
#define LIB_LOAD(name) dlopen(name, RTLD_NOW | RTLD_LOCAL)
#define LIB_SYM(h, sym) dlsym(h, sym)
#define LIB_CLOSE(h) dlclose(h)
#endif
#ifdef CANIM_PLATFORM_LINUX
#define LIB_EXT ".so"
#endif
#ifdef CANIM_PLATFORM_MACOS
#define LIB_EXT ".dylib"
#endif
#ifdef CANIM_PLATFORM_WINDOWS
#include <windows.h>
#define LIB_LOAD(name) LoadLibraryA(name)
#define LIB_SYM(h, sym) GetProcAddress(h, sym)
#define LIB_CLOSE(h) FreeLibrary(h)
#define LIB_EXT ".dll"
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
canim_gfx_load_backend(CanimResult *c_result, CanimGfxBackend backend,
                       const CanimGfxInitInfo *info) {
#ifdef CANIM_POSIX
  dlerror();
#endif
  const char *libname = gfx_backend_libname(backend);
  void *handle = LIB_LOAD(libname);
  const CanimGfxAPI *const *entry =
      (const CanimGfxAPI *const *)LIB_SYM(handle, "GFX_API_ENTRY");
#ifdef CANIM_POSIX
  char *err = dlerror();
  if (err != NULL) {
    CANIM_RESULT_FATAL_EXT(CANIM_RESULT_CODE_LOADING, err);
    dlclose(handle);
    return NULL;
  }
#endif
  CanimGfxContainer *gfx = calloc(1, sizeof(*gfx));
  if (!gfx) {
    LIB_CLOSE(handle);
    CANIM_RESULT_FATAL(CANIM_RESULT_CODE_MEMORY);
    return NULL;
  }
  const CanimGfxAPI *api = *entry;
  gfx->api = *api;
  gfx->impl = NULL;
  gfx->backend = backend;
  CanimGfxDevice *dev = gfx->api.gfx_create_device(c_result, gfx, info);
  if (canim_is_error(c_result)) {
    return NULL;
  }
  gfx->handle = (void *)handle;
  gfx->impl = dev;
  CANIM_RESULT_SUCCESS();
  return gfx;
}

CANIM_API void canim_gfx_unload_backend(CanimResult *c_result,
                                        CanimGfxContainer *gfx) {
  LIB_CLOSE(gfx->handle);
  CANIM_RESULT_SUCCESS();
}
