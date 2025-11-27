// SPDX-License-Identifier: MIT
#include "canim/core.h"
#include "canim/gfx.h"
#include "glad/glad.h"
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
GfxDevice *gl_create_device(CanimResult *result, GfxContainer *container,
                            const GfxInitInfo *info) {
  GfxDevice *dev = (GfxDevice *)calloc(1, sizeof(GfxDevice));
  if (!dev) {
    *result = GFX_DEVICE_CALLOC_ERROR;
    return NULL;
  }
  dev->headless = info->headless;
  dev->height = info->height;
  dev->width = info->width;
  if (dev->headless) {
    dev->egl_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (dev->egl_display == EGL_NO_DISPLAY) {
      free(dev);
      *result = EGL_NO_DISPLAY_ERROR;
      return NULL;
    }

    if (!eglInitialize(dev->egl_display, 0, 0)) {
      free(dev);
      *result = EGL_DISPLAY_INIT_ERROR;
      return NULL;
    }
    EGLint cfg_attr[] = {EGL_SURFACE_TYPE, EGL_PBUFFER_BIT, EGL_RENDERABLE_TYPE,
                         EGL_OPENGL_BIT, EGL_NONE};
    EGLConfig cfg;
    EGLint N;
    if (!eglChooseConfig(dev->egl_display, cfg_attr, &cfg, 1, &N) || N == 0) {
      eglTerminate(dev->egl_display);
      free(dev);
      *result = EGL_DISPLAY_CONFIGURATION_ERROR;
      return NULL;
    }
    EGLint pb_attr[] = {EGL_WIDTH, info->width, EGL_HEIGHT, info->height,
                        EGL_NONE};
    dev->egl_surface = eglCreatePbufferSurface(dev->egl_display, cfg, pb_attr);
    if (dev->egl_surface == EGL_NO_DISPLAY) {
      *result = EGL_NO_SURFACE_ERROR;
      eglTerminate(dev->egl_display);
      free(dev);
      return NULL;
    }
    eglBindAPI(EGL_OPENGL_API);
    dev->egl_context =
        eglCreateContext(dev->egl_display, cfg, EGL_NO_CONTEXT, NULL);
    if (dev->egl_context == EGL_NO_CONTEXT) {
      *result = EGL_NO_CONTEXT_ERROR;
      eglDestroySurface(dev->egl_display, dev->egl_surface);
      eglTerminate(dev->egl_display);
      free(dev);
      return NULL;
    }
    if (!eglMakeCurrent(dev->egl_display, dev->egl_surface, dev->egl_surface,
                        dev->egl_context)) {
      *result = EGL_MAKE_CURRENT_ERROR;
      eglDestroySurface(dev->egl_display, dev->egl_surface);
      eglDestroyContext(dev->egl_display, dev->egl_context);
      eglTerminate(dev->egl_display);
      free(dev);
      return NULL;
    }
  } else {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      *result = SDL_INIT_VIDEO_ERROR;
      free(dev);
      return NULL;
    }
    dev->win = info->native_window
                   ? (SDL_Window *)info->native_window
                   : SDL_CreateWindow("Canim", SDL_WINDOWPOS_CENTERED,
                                      SDL_WINDOWPOS_CENTERED, info->width,
                                      info->height,
                                      SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!dev->win) {
      *result = SDL_WINDOW_CREATION_ERROR;
      SDL_QuitSubSystem(SDL_INIT_VIDEO);
      free(dev);
      return NULL;
    }
    dev->glctx = SDL_GL_CreateContext(dev->win);
    if (!dev->glctx) {
      *result = SDL_GL_CONTEXT_CREATION_ERROR;
      SDL_DestroyWindow(dev->win);
      SDL_QuitSubSystem(SDL_INIT_VIDEO);
      free(dev);
      return NULL;
    }

    SDL_GL_MakeCurrent(dev->win, dev->glctx);
  }
  glViewport(0, 0, dev->width, dev->height);
  glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  if (dev->headless) {
    eglSwapBuffers(dev->egl_display, dev->egl_surface);
    gladLoadGLLoader((GLADloadproc)eglGetProcAddress);
  } else {
    SDL_GL_SwapWindow(dev->win);
    gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
  }

  return dev;
}
void gl_destroy_device(CanimResult *result, GfxContainer *container) {
  GfxDevice *device = container->impl;
  if (!device) {
    return;
  }
  if (device->headless) {
    eglDestroySurface(device->egl_display, device->egl_surface);
    eglDestroyContext(device->egl_display, device->egl_context);
    eglTerminate(device->egl_display);
  } else {
    if (device->glctx) {
      SDL_GL_DeleteContext(device->glctx);
    }
    if (device->win) {
      SDL_DestroyWindow(device->win);
    }
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
  }
  free(device);
};

const GfxAPI GFX_GL_API = {.gfx_create_device = gl_create_device,
                           .gfx_destroy_device = gl_destroy_device};

__attribute__((visibility("default"))) const GfxAPI *GFX_API_ENTRY =
    &GFX_GL_API;
