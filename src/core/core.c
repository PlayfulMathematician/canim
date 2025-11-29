// SPDX-License-Identifier: AGPL-3.0
#include "canim/core.h"
#include <EGL/egl.h>
#include <stdio.h>
void print_error(CanimResult error) {
  if (!IS_AN_ERROR(error)) {
    return;
  }
  switch (error) {
  case GFX_DEVICE_CALLOC_ERROR:
    fprintf(stderr, "When using calloc to allocate memory for"
                    "a GfxDevice, calloc failed\n");
    break;
  case EGL_NO_DISPLAY_ERROR:
    fprintf(stderr, "When creating an EGL display, no display was created\n");
    break;
  case EGL_DISPLAY_INIT_ERROR:
    fprintf(stderr, "When initializing an EGL display something failed.\n");
    break;
  case EGL_DISPLAY_CONFIGURATION_ERROR:
    fprintf(stderr, "When configuring an EGL display something failed.\n");
    break;
  case EGL_NO_SURFACE_ERROR:
    fprintf(stderr, "When creating an EGL surface, no surface was created\n");
    break;
  case EGL_NO_CONTEXT_ERROR:
    fprintf(stderr, "When creating an EGL context, no context was created.\n");
    break;
  case EGL_MAKE_CURRENT_ERROR:
    fprintf(stderr,
            "When the making the EGL context, surface and display the current "
            "one, something failed.\n");
    break;
  case SDL_INIT_VIDEO_ERROR:
    fprintf(stderr, "When initializing SDL video, something failed\n");
    break;
  case SDL_WINDOW_CREATION_ERROR:
    fprintf(stderr, "When making a window with SDL2, something failed\n");
    break;
  case SDL_GL_CONTEXT_CREATION_ERROR:
    fprintf(stderr,
            "When making an OpenGL context with SDL, something failed.\n");
    break;
  case SDL_GLAD_LOAD_ERROR:
    fprintf(stderr, "When loading OpenGL functions with GLAD, using SDL, "
                    "something failed\n");
    break;
  case EGL_GLAD_LOAD_ERROR:
    fprintf(stderr, "When loading OpenGL functions with GLAD, using EGL, "
                    "something failed\n");
    break;
  case SVEC_ZERO_ELEMENT_SIZE:
    fprintf(stderr,
            "When initializing an SVec, the element size was set to zero\n");
    break;
  case SVEC_REALLOC_FAIL:
    fprintf(stderr, "When reallocating space for an SVec, something failed.\n");
    break;

  default:
    fprintf(stderr, "SOMETHING BAD HAPPENED, WE DON'T KNOW WHAT\n");
    break;
  }
}
