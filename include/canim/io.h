// SPDX-License-Identifier: GPL-3.0
// @file io.h
// @brief This header defines input/output API
#pragma once
#include "canim/core.h"
#include "canim/log.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

// @struct PdfVersion
// @brief This is a struct to store PDF versions
typedef struct {
  // @def major
  // @brief This is the PDF's major version
  CanimU8 major;

  // @def minor
  // @brief This is the PDF's minor version
  CanimU8 minor;
} PdfVersion;

// @def CanimPipe
// @brief This is meant to be a representation of a pipe
typedef FILE *CanimPipe;

// @struct CanimScreenBuffer
// @brief This is meant to store screen buffers
typedef struct {
  // @def width
  // @brief This is the width of the buffer
  CanimU64 width;

  // @def height
  // @brief This is the height of the buffer
  CanimU64 height;

  // @def data
  // @brief This is the actual raw bytes of buffer
  CanimByte *data;
} CanimScreenBuffer;

/// @brief This computes the length of a given file in Canim
/// @param[out] c_log A logger
/// @param f Pointer to the file
/// @return The length of the file
CANIM_API long canim_get_file_length(CanimLogger *c_log, FILE *f);

/// @brief This gets the PDF version of a file
/// @param c_log This is the relevant logger
/// @param f This is the file we must get PDF info about
/// @return the version of the pdf
CANIM_API PdfVersion canim_get_pdf_version(CanimLogger *c_log, FILE *f);

/// @brief This allocates memory for the screen buffer
/// @param c_log This is the logger
/// @param w This is the width
/// @param h This is the height
/// @return A freshly allocated CanimScreenBuffer
CANIM_API CanimScreenBuffer canim_allocate_screen_buffer(CanimLogger *c_log,
                                                         CanimU64 w,
                                                         CanimU64 h);

/// @brief This creates an ffmpeg pipe
/// @param c_log A logger
/// @param w This is the width
/// @param h This is the height
/// @param fps This is the framerate of the pipe
/// @param out This is where we should write the info to
/// @return A pipe
CANIM_API CanimPipe canim_create_ffmpeg_pipe(CanimLogger *c_log, CanimU64 w,
                                             CanimU64 h, CanimU64 fps,
                                             const char *out);
/// @brief This pipes data into ffmpeg
/// @param c_log A logger
/// @param buf This is a screen buffer
/// @param pipe This is the pipe
/// @return A bool as a success status
CANIM_API bool canim_pipe_into_ffmpeg(CanimLogger *c_log, CanimScreenBuffer buf,
                                      CanimPipe pipe);

/// @brief This closes a pipe
/// @param pipe This is a pipe to pipe data into
CANIM_API void canim_close_pipe(CanimPipe pipe);
