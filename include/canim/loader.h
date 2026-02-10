// SPDX-License-Identifier: GPL-3.0
#pragma once
#include "canim/core.h"
#include "canim/gfx.h"

/// @brief This loads a backend and makes a graphics container
/// @param result This is the result of the output
/// @param backend This is the gfx api
/// @param info The relevant info to create the container
/// @return A gfx container
CANIM_API CanimGfxContainer *
canim_gfx_load_backend(CanimResult *result, CanimGfxBackend backend,
                       const CanimGfxInitInfo *info);

/// @brief This unloads a backend
/// @param result This is the result of the output
/// @param gfx This is the container
CANIM_API void canim_gfx_unload_backend(CanimResult *result,
                                        CanimGfxContainer *gfx);
