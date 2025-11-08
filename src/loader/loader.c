
#include <canim/core.h>
#include <canim/loader.h>
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

const char *gfx_backend_libname(GfxBackend backend) {
  switch (backend) {
  case CANIM_GFX_GL:
    return "gl" LIB_EXT;

  default:
    return NULL;
  }
}
