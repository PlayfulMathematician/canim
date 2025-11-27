// SPDX-License-Identifier: MIT
#pragma once
#include "canim/core.h"
#include "canim/gfx.h"

/// @brief This loads a backend and makes a graphics container
/// @param result This is the result of the output
/// @param backend This is the gfx api
/// @param info The relevant info to create the container
/// @return A gfx container
CANIM_API GfxContainer *gfx_load_backend(CanimResult *result,
                                         GfxBackend backend,
                                         const GfxInitInfo *info);

/// @brief This unloads a backend
/// @param result This is the result of the output
/// @param gfx This is the container
CANIM_API void gfx_unload_backend(CanimResult *result, GfxContainer *gfx);
