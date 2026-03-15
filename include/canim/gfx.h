// SPDX-License-Identifier: GPL-3.0
// @file gfx.h
// @brief This header defines the GFX Api wrapper
#pragma once
#include "canim/core.h"
#include "canim/io.h"
#include "canim/log.h"
#include <stdbool.h>
/// @enum GfxBackend
/// @brief This is a list of available backends
typedef enum {
  /// @def CANIM_GFX_NONE
  /// @brief This is for no graphics API
  CANIM_GFX_NONE = 0,
  /// @def CANIM_GFX_GL
  /// @brief This is for an OpenGL graphics API
  CANIM_GFX_GL = 1,
} CanimGfxBackend;

/// @brief GFX API Specific struct
typedef struct CanimGfxDevice CanimGfxDevice;

/// @brief This container contains the graphics stuff
typedef struct CanimGfxContainer CanimGfxContainer;

/// @brief This stores the function pointers for implementation of gfx api's
typedef struct CanimGfxAPI CanimGfxAPI;

/// @struct GfxInitInfo
/// @brief This struct stores info neccesary to initialize graphics
typedef struct {
  /// @def headless
  /// @brief This variable specifies if the device should be headless
  bool headless;

  /// @def native_window
  /// @brief This is a pointer to the native window
  void *native_window;

  /// @def width
  /// @brief This is the width of the device
  int width;

  /// @def height
  /// @brief This is the height of the device
  int height;
} CanimGfxInitInfo;

/// @struct GfxAPI
/// @brief This struct stores the cross platform API functions
struct CanimGfxAPI {
  /// @brief This constructs a graphics device
  /// @param[out] CanimLogger* This is the error status
  /// @param CanimGfxContainer* This is the container
  /// @param CanimGfxInitInfo* This is the initialization info
  /// @return A graphics device
  CanimGfxDevice *(*gfx_create_device)(CanimLogger *, CanimGfxContainer *,
                                       const CanimGfxInitInfo *);
  /// @brief This sets up the shaders
  /// @param[out] CanimLogger* This is the error status
  /// @param CanimGfxContainer* This is the container
  bool (*gfx_setup_shaders)(CanimLogger *, CanimGfxContainer *);

  /// @brief This destroys a graphics device
  /// @param[out] CanimLogger* This is the error status
  /// @param CanimGfxContainer* This is the graphics container
  void (*gfx_destroy_device)(CanimLogger *, CanimGfxContainer *);

  /// @brief This swaps swaps buffer
  /// @param[out] CanimLogger* This is the status
  /// @param CanimGfxContainer* The graphics container
  void (*gfx_swap_buffers)(CanimLogger *, CanimGfxContainer *);

  /// @brief This checks if the system should close
  /// @param[out] CanimLogger* This is the status
  /// @param CanimGfxContainer* This is the graphics container
  /// @param close A bool pointerto keep track of whether or not to close
  void (*gfx_should_close)(CanimLogger *, CanimGfxContainer *, bool *);
  /// @brief This saves the screen in a buffer
  /// @param[out] CanimLogger* CanimLogger
  /// @param CanimGfxContainer* This is the graphics container
  /// @param CanimScreenBuffer This is the buffer
  void (*gfx_save_screen)(CanimLogger *, CanimGfxContainer *,
                          CanimScreenBuffer);
  /// @brief This draws a mesh
  /// @param[out] CanimLogger* the CanimLogger
  /// @param CanimGfxContainer* This is the relevant graphics container
  /// @param float* This is the list of vertices
  /// @param unsigned int* This is the list of indices
  /// @param int This is the number of vertices
  /// @param This is the number of triangles
  void (*gfx_draw_mesh)(CanimLogger *, CanimGfxContainer *, float *,
                        unsigned int *, int, int);
};

/// @struct GfxContainer
struct CanimGfxContainer {
  /// @def api
  /// @brief This is the VTable storing gfx api commands
  CanimGfxAPI api;

  /// @def impl
  /// @brief This is the implementation specific graphics device
  CanimGfxDevice *impl;

  /// @def backend
  /// @brief This is the backend to the graphics api
  CanimGfxBackend backend;

  /// @def handle
  /// @brief This is the handle to the dynamically loaded backend
  void *handle;
};
