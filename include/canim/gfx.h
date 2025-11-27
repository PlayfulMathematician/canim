// SPDX-License-Identifier: MIT
#pragma once
#include "canim/core.h"
#include <stdbool.h>

/// @enum GfxBackend
/// @brief This is a list of available backends
typedef enum {
  CANIM_GFX_NONE = 0, ///< No Graphics API used
  CANIM_GFX_GL = 1,   ///< OpenGL in use
} GfxBackend;

/// @brief GFX API Specific struct
typedef struct GfxDevice GfxDevice;

/// @brief This container contains the graphics stuff
typedef struct GfxContainer GfxContainer;

/// @brief This stores the function pointers for implementation of gfx api's
typedef struct GfxAPI GfxAPI;

/// @struct GfxInitInfo
/// @brief This struct stores info neccesary to initialize graphics
typedef struct {
  bool headless;       ///< This stores whether or not the window is headless
  void *native_window; ///< This stores a pointer to a native window
  int width;           ///< The width of the window
  int height;          ///< The height of it
} GfxInitInfo;

/// @struct GfxAPI
/// @brief This struct stores the cross platform API functions
/// This struct has a fptr, but i am not gonna document it, because i believe in
/// freedom and you can't stop me
struct GfxAPI {
  GfxDevice *(*gfx_create_device)(CanimResult *, GfxContainer *,
                                  const GfxInitInfo *);
  void (*gfx_destroy_device)(CanimResult *, GfxContainer *);
};

/// @struct GfxContainer
struct GfxContainer {
  GfxAPI api;         ///< The API
  GfxDevice *impl;    ///< The Implementation specfic gfxdevice
  GfxBackend backend; ///< The backend
  void *handle;       ///< Handle to the dynamic lib
};
