#include "./gfx_api.h"
#include <EGL/egl.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_video.h>
#include <stdlib.h>
struct GfxDevice {
  bool headless;
  int width;
  int height;
  SDL_GLContext glctx;
  SDL_Window *win;
  EGLDisplay egl_display;
  EGLSurface egl_surface;
  EGLContext egl_context;
};
CANIM_API GfxDevice *gfx_create_device(CanimResult *result,
                                       const GfxInitInfo *info) {
  GfxDevice *dev = (GfxDevice *)calloc(1, sizeof(GfxDevice));
  dev->headless = info->headless;
  dev->height = info->height;
  dev->width = info->width;
  if (dev->headless) {
    dev->egl_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    eglInitialize(dev->egl_display, 0, 0);
    EGLint cfg_attr[] = {EGL_SURFACE_TYPE, EGL_PBUFFER_BIT, EGL_RENDERABLE_TYPE,
                         EGL_OPENGL_BIT, EGL_NONE};
    EGLConfig cfg;
    EGLint N;
    eglChooseConfig(dev->egl_display, cfg_attr, &cfg, 1, &N);
    EGLint pb_attr[] = {EGL_WIDTH, info->width, EGL_HEIGHT, info->height,
                        EGL_NONE};
    dev->egl_surface = eglCreatePbufferSurface(dev->egl_display, cfg, pb_attr);
    eglBindAPI(EGL_OPENGL_API);
    dev->egl_context =
        eglCreateContext(dev->egl_display, cfg, EGL_NO_CONTEXT, NULL);
    eglMakeCurrent(dev->egl_display, dev->egl_surface, dev->egl_surface,
                   dev->egl_context);
  } else {
    SDL_Init(SDL_INIT_VIDEO);
    dev->win = info->native_window
                   ? (SDL_Window *)info->native_window
                   : SDL_CreateWindow("Canim", SDL_WINDOWPOS_CENTERED,
                                      SDL_WINDOWPOS_CENTERED, info->width,
                                      info->height,
                                      SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    dev->glctx = SDL_GL_CreateContext(dev->win);
    SDL_GL_MakeCurrent(dev->win, dev->glctx);
  }
  glViewport(0, 0, dev->width, dev->height);
  return dev;
}
