// SPDX-License-Identifier: MIT

#include "canim/core.h"
#include "canim/gfx.h"
#include "canim/log.h"
#include "glad/glad.h"
#ifdef CANIM_PLATFORM_LINUX
#include <EGL/egl.h>
#endif

#include <GL/gl.h>
#ifdef CANIM_PLATFORM_MACOS

#include <OpenGL/CGLCurrent.h>
#include <OpenGL/CGLTypes.h>
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>
#endif
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_video.h>
#include <stdlib.h>
struct CanimGfxDevice {
  bool headless;
  int width;
  int height;
  SDL_GLContext sdl_glctx;
  SDL_Window *sdl_win;
#ifdef CANIM_PLATFORM_LINUX
  EGLDisplay egl_display;
  EGLSurface egl_surface;
  EGLContext egl_context;
#endif
#ifdef CANIM_PLATFORM_MACOS
  CGLContextObj cgl_ctx;
#endif
};
CanimGfxDevice *gl_create_device(CanimLogger *c_log,
                                 CanimGfxContainer *container,
                                 const CanimGfxInitInfo *info) {
  CanimGfxDevice *dev = (CanimGfxDevice *)calloc(1, sizeof(CanimGfxDevice));
  if (!dev) {
    CANIM_LOG_ERROR("Allocating a graphics device failed!");
    return NULL;
  }
  CANIM_LOG_INFO("Allocated a graphics deviced");
  dev->headless = info->headless;
  dev->height = info->height;
  dev->width = info->width;
  if (dev->headless) {
#ifdef CANIM_PLATFORM_MACOS
    CGLError err = kCGLNoError;
    CGLPixelFormatAttribute attrs[] = {
        kCGLPFAOpenGLProfile,
        (CGLPixelFormatAttribute)kCGLOGLPVersion_3_2_Core,
        kCGLPFAAccelerated,
        kCGLPFADoubleBuffer,
        kCGLPFAColorSize,
        (CGLPixelFormatAttribute)24,
        kCGLPFAAlphaSize,
        (CGLPixelFormatAttribute)8,
        kCGLPFADepthSize,
        (CGLPixelFormatAttribute)24,
        (CGLPixelFormatAttribute)0};

    CGLPixelFormatObj pixelFormat;
    GLint npix;

    err = CGLChoosePixelFormat(attrs, &pixelFormat, &npix);
    if (err != kCGLNoError) {
      const char *errStr = CGLErrorString(err);
      CANIM_RESULT_FATAL_EXT(CANIM_RESULT_CODE_GFX, errStr); // NOLINT
      return NULL;
    }
    CGLContextObj cglctx = NULL;
    err = CGLCreateContext(pixelFormat, NULL, &cglctx);
    if (err != kCGLNoError) {
      CGLReleasePixelFormat(pixelFormat);
      const char *errStr = CGLErrorString(err);
      CANIM_RESULT_FATAL_EXT(CANIM_RESULT_CODE_GFX, errStr); // NOLINT
      return NULL;
    }
    dev->cgl_ctx = cglctx;

    CGLReleasePixelFormat(pixelFormat);

    err = CGLSetCurrentContext(cglctx);
    if (err != kCGLNoError) {
      CGLDestroyContext(cglctx);
      const char *errStr = CGLErrorString(err);
      CANIM_RESULT_FATAL_EXT(CANIM_RESULT_CODE_GFX, errStr); // NOLINT
      return NULL;
    }

#endif
#ifdef CANIM_PLATFORM_LINUX
    dev->egl_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (dev->egl_display == EGL_NO_DISPLAY) {
      free(dev);
      CANIM_LOG_ERROR("Getting an EGL display failed");
      return NULL;
    }

    CANIM_LOG_INFO("Got the EGL display");

    if (!eglInitialize(dev->egl_display, 0, 0)) {
      free(dev);

      CANIM_LOG_ERROR("Initializing an EGL display failed");

      return NULL;
    }
    CANIM_LOG_INFO("Initalized an EGL display");
    EGLint cfg_attr[] = {EGL_SURFACE_TYPE, EGL_PBUFFER_BIT, EGL_RENDERABLE_TYPE,
                         EGL_OPENGL_BIT, EGL_NONE};
    EGLConfig cfg;
    EGLint N;
    if (!eglChooseConfig(dev->egl_display, cfg_attr, &cfg, 1, &N) || N == 0) {
      eglTerminate(dev->egl_display);
      free(dev);

      CANIM_LOG_ERROR("Configuring an EGL display failed");

      return NULL;
    }
    EGLint pb_attr[] = {EGL_WIDTH, info->width, EGL_HEIGHT, info->height,
                        EGL_NONE};
    dev->egl_surface = eglCreatePbufferSurface(dev->egl_display, cfg, pb_attr);
    if (dev->egl_surface == EGL_NO_DISPLAY) {

      CANIM_LOG_ERROR("Creating an EGL surface failed");
      eglTerminate(dev->egl_display);
      free(dev);
      return NULL;
    }

    CANIM_LOG_INFO("Created an EGL surface");
    eglBindAPI(EGL_OPENGL_API);
    dev->egl_context =
        eglCreateContext(dev->egl_display, cfg, EGL_NO_CONTEXT, NULL);
    if (dev->egl_context == EGL_NO_CONTEXT) {

      CANIM_LOG_ERROR("Creating an EGL context failed");
      eglDestroySurface(dev->egl_display, dev->egl_surface);
      eglTerminate(dev->egl_display);
      free(dev);
      return NULL;
    }

    CANIM_LOG_INFO("Created an EGL context");
    if (!eglMakeCurrent(dev->egl_display, dev->egl_surface, dev->egl_surface,
                        dev->egl_context)) {

      CANIM_LOG_ERROR(
          "Attaching an EGL rendering context to EGL surface failed");
      eglDestroySurface(dev->egl_display, dev->egl_surface);
      eglDestroyContext(dev->egl_display, dev->egl_context);
      eglTerminate(dev->egl_display);
      free(dev);
      return NULL;
    }

    CANIM_LOG_INFO("Attached an EGL rendering context to EGL surface");
#endif
  } else {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {

      CANIM_LOG_ERROR("Initializing SDL_video failed");
      free(dev);
      return NULL;
    }

    CANIM_LOG_INFO("Initialized SDL_video mode");
    dev->sdl_win = info->native_window
                       ? (SDL_Window *)info->native_window
                       : SDL_CreateWindow(
                             "Canim", SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED, info->width, info->height,
                             SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!dev->sdl_win) {

      CANIM_LOG_ERROR("Initializing SDL_window failed");

      SDL_QuitSubSystem(SDL_INIT_VIDEO);
      free(dev);
      return NULL;
    }

    CANIM_LOG_INFO("Initialized an SDL_window");
    dev->sdl_glctx = SDL_GL_CreateContext(dev->sdl_win);
    if (!dev->sdl_glctx) {

      CANIM_LOG_ERROR("Creating an SDL_OpenGL Context failed");
      SDL_DestroyWindow(dev->sdl_win);
      SDL_QuitSubSystem(SDL_INIT_VIDEO);
      free(dev);
      return NULL;
    }

    CANIM_LOG_INFO("Created an SDL_OpenGL Context");

    SDL_GL_MakeCurrent(dev->sdl_win, dev->sdl_glctx);
  }
  if (dev->headless) {
#ifdef CANIM_PLATFORM_MACOS
    if (!gladLoadGL()) {
      CANIM_RESULT_FATAL(CANIM_RESULT_CODE_GFX);
    }
#endif
#ifdef CANIM_PLATFORM_LINUX
    gladLoadGLLoader((GLADloadproc)eglGetProcAddress);
#endif
  } else {
    gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
  }
  glViewport(0, 0, dev->width, dev->height);
  glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  if (dev->headless) {
#ifdef CANIM_PLATFORM_LINUX
    eglSwapBuffers(dev->egl_display, dev->egl_surface);
#endif
  } else {
    SDL_GL_SwapWindow(dev->sdl_win);
  }

  return dev;
}

void gl_swap_buffers(CanimLogger *c_log, CanimGfxContainer *container) {
  CanimGfxDevice *dev = container->impl;
  if (dev->headless) {
#ifdef CANIM_PLATFORM_LINUX
    eglSwapBuffers(dev->egl_display, dev->egl_surface);
#endif
  } else {
    SDL_GL_SwapWindow(dev->sdl_win);
  }
}
void gl_destroy_device(CanimLogger *c_log, CanimGfxContainer *container) {
  CanimGfxDevice *device = container->impl;
  if (!device) {
    return;
  }
  if (device->headless) {
#ifdef CANIM_PLATFORM_LINUX
    eglDestroySurface(device->egl_display, device->egl_surface);
    eglDestroyContext(device->egl_display, device->egl_context);
    eglTerminate(device->egl_display);
#endif
#ifdef CANIM_PLATFORM_MACOS
    CGLSetCurrentContext(NULL);
    CGLDestroyContext(device->cgl_ctx);
#endif
  } else {
    if (device->sdl_glctx) {
      SDL_GL_DeleteContext(device->sdl_glctx);
    }
    if (device->sdl_win) {
      SDL_DestroyWindow(device->sdl_win);
    }
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
  }
  free(device);
};

void gl_should_close(CanimLogger *c_log, CanimGfxContainer *container,
                     bool *close) {
  if (!container->impl->headless) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT ||
          (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
        *close = false;
      }
    }
  }
}
/*
 *glPixelStorei(GL_PACK_ALIGNMENT, 1);
  glReadPixels(0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, rgb); */
void gl_save_screen(CanimLogger *c_log, CanimGfxContainer *container,
                    CanimScreenBuffer buf) {
  glPixelStorei(GL_PACK_ALIGNMENT, 1);
  glReadPixels(0, 0, container->impl->width, container->impl->height, GL_RGB,
               GL_UNSIGNED_BYTE, buf.data);
};

const CanimGfxAPI GFX_GL_API = {.gfx_create_device = gl_create_device,
                                .gfx_destroy_device = gl_destroy_device,
                                .gfx_swap_buffers = gl_swap_buffers,
                                .gfx_should_close = gl_should_close,
                                .gfx_save_screen = gl_save_screen};

CANIM_API const CanimGfxAPI *GFX_API_ENTRY = &GFX_GL_API;
