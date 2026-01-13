// SPDX-License-Identifier: AGPL-3.0
#pragma once
#include "canim/core.h"
#include <stdbool.h>

/// @enum GfxBackend
/// @brief This is a list of available backends
typedef enum {
  CANIM_GFX_NONE = 0, ///< No Graphics API used
  CANIM_GFX_GL = 1,   ///< OpenGL in use
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
  bool headless;       ///< This stores whether or not the window is headless
  void *native_window; ///< This stores a pointer to a native window
  int width;           ///< The width of the window
  int height;          ///< The height of it
} CanimGfxInitInfo;

/// @struct GfxAPI
/// @brief This struct stores the cross platform API functions
/// This struct has a fptr, but i am not gonna document it, because i believe in
/// freedom and you can't stop me
struct CanimGfxAPI {
  /// @brief This constructs a graphics device
  /// @param[out] CanimResult* This is the error status
  /// @param CanimGfxContainer* This is the container
  /// @param CanimGfxInitInfo* This is the initialization info
  /// @return A graphics device
  CanimGfxDevice *(*gfx_create_device)(CanimResult *, CanimGfxContainer *,
                                       const CanimGfxInitInfo *);
  /// @brief This destroys a graphics device
  /// @param[out] CanimResult* This is the error status
  /// @param CanimGfxContainer* This is the graphics container
  void (*gfx_destroy_device)(CanimResult *, CanimGfxContainer *);
};

/// @struct GfxContainer
struct CanimGfxContainer {
  CanimGfxAPI api;         ///< The API
  CanimGfxDevice *impl;    ///< The Implementation specfic gfxdevice
  CanimGfxBackend backend; ///< The backend
  void *handle;            ///< Handle to the dynamic lib
};
