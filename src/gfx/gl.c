// SPDX-License-Identifier: GPL-3.0

#include "canim/core.h"
#include "canim/gfx.h"
#include "canim/log.h"
#include "glad/glad.h"
#include <SDL_error.h>
#ifdef CANIM_PLATFORM_LINUX
#include <EGL/egl.h>
#include <GL/gl.h>
#endif

#ifdef CANIM_PLATFORM_MACOS

#include <OpenGL/CGLCurrent.h>
#include <OpenGL/CGLTypes.h>
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>
#define GL_SILENCE_DEPRECATION 0
#endif
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_video.h>
#include <stdlib.h>
enum { CANIM_TRIANGLE_SHADER = 0, CANIM_LAST_SHADER };
typedef GLuint CanimShaderList[CANIM_LAST_SHADER];

struct CanimGfxDevice {
  bool headless;
  int width;
  int height;
  CanimShaderList shaders;
  SDL_GLContext sdl_glctx;
  SDL_Window *sdl_win;
#ifdef CANIM_PLATFORM_LINUX
  EGLDisplay egl_display;
  EGLSurface egl_surface;
  EGLContext egl_context;
#endif
#ifdef CANIM_PLATFORM_MACOS
  CGLContextObj cgl_ctx;
  CGLPBufferObj cgl_pbuf;
#endif
};
const char *VS_LIST[CANIM_LAST_SHADER] = {
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aNorm;\n"
    "out vec4 v_position;\n"
    "out vec3 v_norm;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "   v_position = gl_Position;\n"
    "   v_norm = aNorm;\n"
    "}\0"};

const char *FS_LIST[CANIM_LAST_SHADER] = {
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec4 v_position;\n"
    "in vec3 v_norm;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(abs(normalize(v_norm).z) * vec3(1.0, 1.0, 1.0),1.0);\n"
    "}\0"};
// add logging
GLuint compile_shaders(CanimLogger *c_log, const char *shader, GLenum type) {
  GLuint shader_id = glCreateShader(type);
  glShaderSource(shader_id, 1, &shader, NULL);
  glCompileShader(shader_id);

  GLint compile_status;

  glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compile_status);
  return shader_id;
}
GLuint link_program(GLuint vertex_shader_id, GLuint fragment_shader_id) {
  GLuint program_id = glCreateProgram();
  glAttachShader(program_id, vertex_shader_id);
  glAttachShader(program_id, fragment_shader_id);

  glLinkProgram(program_id);

  GLint link_status;

  glGetProgramiv(program_id, GL_LINK_STATUS, &link_status);
  glDeleteShader(vertex_shader_id);
  glDeleteShader(fragment_shader_id);
  return program_id;
}

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
        kCGLPFAAccelerated, kCGLPFAOpenGLProfile,
        (CGLPixelFormatAttribute)kCGLOGLPVersion_3_2_Core, 0};

    CGLPixelFormatObj pixelFormat;
    GLint npix;

    err = CGLChoosePixelFormat(attrs, &pixelFormat, &npix);
    if (err != kCGLNoError) {
      const char *errStr = CGLErrorString(err);
      CANIM_LOG_ERROR("Choosing a pixel format failed: %s",
                      errStr); // NOLINT
      return NULL;
    }
    CANIM_LOG_INFO("Chose a pixel format");
    CGLContextObj cglctx = NULL;
    err = CGLCreateContext(pixelFormat, NULL, &cglctx);
    if (err != kCGLNoError) {
      CGLReleasePixelFormat(pixelFormat);
      const char *errStr = CGLErrorString(err);
      CANIM_LOG_ERROR("Creating an CGL context failed: %s",
                      errStr); // NOLINT
      return NULL;
    }
    CANIM_LOG_INFO("Created a CGL context");
    dev->cgl_ctx = cglctx;

    CGLReleasePixelFormat(pixelFormat);
    CGLPBufferObj pbuffer;
    err = CGLCreatePBuffer(info->width, info->height, GL_TEXTURE_2D, GL_RGBA, 0,
                           &pbuffer);
    if (err != kCGLNoError) {
      const char *errStr = CGLErrorString(err);
      CANIM_LOG_ERROR("Creating a CGL pbuffer failed: %s",
                      errStr); // NOLINT
      return NULL;
    }

    err = CGLSetPBuffer(cglctx, pbuffer, 0, 0, 0);
    if (err != kCGLNoError) {
      const char *errStr = CGLErrorString(err);
      CANIM_LOG_ERROR("Setting a CGL pbuffer failed: %s", errStr); // NOLINT
      return NULL;
    }
    err = CGLSetCurrentContext(cglctx);
    if (err != kCGLNoError) {
      CGLDestroyContext(cglctx);
      const char *errStr = CGLErrorString(err);
      CANIM_LOG_ERROR("Setting the CGL context failed: %s",
                      errStr); // NOLINT
      return NULL;
    }
    CANIM_LOG_INFO("Set a CGL Context");
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

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

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

    if (SDL_GL_MakeCurrent(dev->sdl_win, dev->sdl_glctx) < 0) {
      CANIM_LOG_ERROR("Making an SDL GL context current failed: %s",
                      SDL_GetError());
      return (CanimGfxDevice *)0;
    }
    CANIM_LOG_INFO("Made an SDL context current");
  }
  if (dev->headless) {
#ifdef CANIM_PLATFORM_MACOS
    if (!gladLoadGL()) {
      CANIM_LOG_ERROR("Loading Glad Failed");
      return (CanimGfxDevice *)0;
    }
#endif
#ifdef CANIM_PLATFORM_LINUX
    gladLoadGLLoader((GLADloadproc)eglGetProcAddress);
#endif
  } else {
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
      CANIM_LOG_ERROR("Loading with Glad failed");
    }
    CANIM_LOG_INFO("Loaded external functions with GLAD");
  }
  glViewport(0, 0, dev->width, dev->height);
  if (dev->headless) {
#ifdef CANIM_PLATFORM_LINUX
    eglSwapBuffers(dev->egl_display, dev->egl_surface);
#endif
#ifdef CANIM_PLATFORM_MACOS
    CGLFlushDrawable(dev->cgl_ctx);
#endif
  } else {
    SDL_GL_SwapWindow(dev->sdl_win);
  }

  return dev;
}

void gl_swap_buffers(CanimLogger *c_log, CanimGfxContainer *container) {

  CanimGfxDevice *dev = container->impl;
  glViewport(0, 0, dev->width, dev->height);
  // glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  // glClear(GL_COLOR_BUFFER_BIT);
  if (dev->headless) {
#ifdef CANIM_PLATFORM_LINUX
    eglSwapBuffers(dev->egl_display, dev->egl_surface);
#endif
#ifdef CANIM_PLATFORM_MACOS
    CGLFlushDrawable(container->impl->cgl_ctx);
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

bool gl_setup_shaders(CanimLogger *c_log, CanimGfxContainer *container) {
  for (int i = 0; i < CANIM_LAST_SHADER; i++) {
    GLuint vs, fs, s;
    vs = compile_shaders(c_log, VS_LIST[i], GL_VERTEX_SHADER);
    fs = compile_shaders(c_log, FS_LIST[i], GL_FRAGMENT_SHADER);
    s = link_program(vs, fs);
    container->impl->shaders[i] = s;
  }
  return true;
}
void gl_draw_mesh(CanimLogger *c_log, CanimGfxContainer *container,
                  float *vertices, int vertex_size) {

  unsigned int VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertex_size, vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  glUseProgram(container->impl->shaders[CANIM_TRIANGLE_SHADER]);

  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, vertex_size / (6 * sizeof(float)));
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
}

const CanimGfxAPI GFX_GL_API = {.gfx_create_device = gl_create_device,
                                .gfx_destroy_device = gl_destroy_device,
                                .gfx_swap_buffers = gl_swap_buffers,
                                .gfx_should_close = gl_should_close,
                                .gfx_save_screen = gl_save_screen,
                                .gfx_setup_shaders = gl_setup_shaders,
                                .gfx_draw_mesh = gl_draw_mesh};

CANIM_API const CanimGfxAPI *GFX_API_ENTRY = &GFX_GL_API;
