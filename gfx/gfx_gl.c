#include "./gfx_api.h"
#include <EGL/egl.h>
#include <GL/gl.h>
#include <stdlib.h>
struct GfxDevice {
  bool headless;
  int width;
  int height;
  EGLDisplay egl_dpy;
  EGLSurface egl_surf;
  EGLContext egl_ctx;
};
CANIM_API GfxDevice *gfx_create_device(CanimResult *result,
                                       const GfxInitInfo *info) {
  GfxDevice *dev = (GfxDevice *)calloc(1, sizeof(GfxDevice));
  dev->headless = info->headless;
  dev->height = info->height;
  dev->width = info->width;
  return dev;
}
