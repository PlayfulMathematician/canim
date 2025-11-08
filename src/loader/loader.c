
#include "canim/loader.h"
#include "canim/core.h"
#include <stdlib.h>
#ifdef CANIM_PLATFORM_POSIX
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

#endif
const char *gfx_backend_libname(GfxBackend backend) {
  switch (backend) {
  case CANIM_GFX_GL:
    return "gl" LIB_EXT;

  default:
    return NULL;
  }
}
GfxContainer *gfx_load_backend(CanimResult *result, GfxBackend backend,
                               const GfxInitInfo *info) {
  const char *libname = gfx_backend_libname(backend);
  LIB_HANDLE handle = LIB_LOAD(libname);
  const GfxAPI *api = (const GfxAPI *)LIB_SYM(handle, "GFX_API_ENTRY");
  GfxContainer *gfx = calloc(1, sizeof(*gfx));
  gfx->api = *api;
  gfx->impl = NULL;
  gfx->backend = backend;
  GfxDevice *dev = gfx->api.gfx_create_device(result, gfx, info);
  gfx->impl = dev;
  *result = SUCCESS;
  return gfx;
}
