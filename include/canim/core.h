// SPDX-License-Identifier: MIT
#pragma once
#include <stdint.h>
#include <sys/types.h>
#define CANIM_API __attribute__((visibility("default")))

// status code helpers
#define STATUS_TYPE_SHIFT 24
#define STATUS_TYPE_MASK 0xFF000000
#define STATUS_INFO_MASK 0x00FFFFFF

/// @brief Operation succeeded.
#define SUCCESS 0x00

/// @brief No operation performed.
#define NOOP 0x01

/// @brief Non-fatal error.
#define NONFATAL 0x02

/// @brief Fatal error.
#define FATAL 0x03

/// @brief Extracts the status type (SUCCESS/NOOP/NONFATAL/FATAL).
#define STATUS_TYPE(code) (((code) & STATUS_TYPE_MASK) >> STATUS_TYPE_SHIFT)

/// @brief True if code is an error (NONFATAL or FATAL).
#define IS_AN_ERROR(x)                                                         \
  ((STATUS_TYPE((x)) == FATAL) || (STATUS_TYPE((x)) == NONFATAL))
/// @brief This are all of the error codes
enum {
  TRI_INIT_MALLOC_FAIL = (uint32_t)0x03000000,
  TRI_NOT_FOUND,
  ADDING_TRI_REALLOC_FAILURE,
  PSLG_INIT_MALLOC_ERROR,
  PSLG_VERTEX_MALLOC_ERROR,
  PSLG_EDGE_MALLOC_ERROR,
  PSLG_EDGE_SPLIT_VERTEX_REALLOC_ERROR,
  PSLG_EDGE_SPLIT_EDGE_REALLOC_ERROR,
  PSLG_TRIANGULATION_INIT_MALLOC_ERROR,
  PSLG_ATTACK_TEMP_EDGES_MALLOC_ERROR,
  PSLG_ATTACK_EDGE_REALLOCATION_ERROR,
  TRIANGULATE_POLYHEDRON_BATCH_TRIANGULATIONS_MALLOC_ERROR,
  TRIANGULATE_POLYHEDRON_VERTEX_MALLOC_ERROR,
  POLYHEDRON_MALLOC_ERROR,
  POLYHEDRON_VERTEX_MALLOC_ERROR,
  POLYHEDRON_FACE_MALLOC_ERROR,
  POLYHEDRON_FACE_SIZES_MALLOC_ERROR,
  FILE_NO_CLEAN_LINE_OFF_ERROR,
  OFF_HEADER_OFF_ERROR,
  OFF_HEADER_DATA_ERROR,
  OFF_VERTEX_ERROR,
  OFF_FACE_ERROR,
  DEDUP_PSLG_VERTEX_REALLOC_ERROR,
  DEDUP_PSLG_EDGES_REALLOC_ERROR,
  STL_HEADER_WRITE_ERROR,
  STL_VECTOR_WRITE_ERROR,
  RGB_BUFFER_MALLOC_ERROR,
  LOAD_OPENGL_FUNCTION_ERROR,
  OPENGL_SHADER_COMPILATION_ERROR,
  OPENGL_SHADER_PROGRAM_LINK_ERROR,
  DRAW_TRIANGULATION_MALLOC_ERROR,
  TRI_CLONE_ERROR,
  TRI_CLONE_TRI_ERROR,
  PDF_XREF_FIND_SEEK_END_ERROR,
  PDF_XREF_FIND_FTELL_ERROR,
  PDF_XREF_FIND_SEEK_SET_ERROR,
  PDF_XREF_STARTXREF_NOT_FOUND,
  PDF_XREF_OFFSET_PARSE_ERROR,
  PDF_XREF_FIND_FREAD_ERROR,
  NEXT_STR_NOT_FOUND_ERROR,
  GET_XREF_FSEEK_ERROR,
  GET_XREF_FREAD_ERROR,
  GET_XREF_STRCHR_NEWLINE_FAIL,
  NON_XREF_XREF,
  GET_XREF_STREAM_SEEK_ERROR,
  STREAM_DECOMPRESS_MALLOC_FAIL,
  STREAM_DECOMPRESS_INIT_FAIL,
  STREAM_DECOMPRESS_FAIL,
  GET_XREF_STREAM_MALLOC_ERROR,
  GET_XREF_STREAM_READ_ERROR,
  GET_XREF_MALLOC_ERROR,
  GET_XREF_TABLE_ENTRIES_MALLOC_ERROR,
  GL_GFX_DEVICE_CALLOC_ERROR,
  EGL_NO_DISPLAY_ERROR,
  EGL_DISPLAY_INIT_ERROR,
  EGL_DISPLAY_CONFIGURATION_ERROR,
  EGL_NO_SURFACE_ERROR,
  EGL_NO_CONTEXT_ERROR,
  EGL_MAKE_CURRENT_ERROR,
  SDL_INIT_VIDEO_ERROR,
  SDL_WINDOW_CREATION_ERROR,
  SDL_GL_CONTEXT_CREATION_ERROR
};
typedef uint32_t CanimResult;
/**
 * @brief Print out the error
 * @param error The error the need be printed.
 * @return I will not return anything
 */
void print_error(CanimResult error);

#ifdef _WIN32
#define CANIM_PLATFORM_WINDOWS 1
#define CANIM_PLATFORM_KNOWN 1
#endif
#ifdef __APPLE__
#define CANIM_PLATFORM_MAC 1
#define CANIM_PLATFORM_KNOWN 1
#endif
#ifdef __linux__
#define CANIM_PLATFORM_LINUX 1
#define CANIM_PLATFORM_KNOWN 1
#endif
#ifdef CANIM_PLATFORM_LINUX
#define CANIM_PLATFORM_POSIX 1
#define CANIM_PLATFORM_KNOWN 1
#endif
#ifdef CANIM_PLATFORM_MAC
#define CANIM_PLATFORM_POSIX 1
#define CANIMCANIM_PLATFORM_KNOWN 1
#endif
#ifndef CANIM_PLATFORM_KNOWN
#define CANIM_PLATFORM_UNKNOWN 1
#endif
/// @def max
/// @brief The maximizer
#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif

/// @def EPSILON
/// @brief Tolerance for floating-point comparisons.
#define EPSILON 0.000001

/// @def null
/// @brief I do not want to capitalize NULL
#define null NULL

/// @def BUFFER_SIZE
/// @brief The size of a buffer
#define BUFFER_SIZE 4096

/// @def BIT_IGNORE
/// @brief Alignment granularity in bits (round up to 2^BIT_IGNORE).
#define BIT_IGNORE 4

/// @def BIT_SIZE
/// @brief 2 ^ BIT_IGNORE - 1
#define BIT_SIZE ((1 << BIT_IGNORE) - 1)

/// @def BIT_ALIGN(x)
/// @brief Round x up to nearest aligned multiple.
#define BIT_ALIGN(x) max(((x) + BIT_SIZE) & ~BIT_SIZE, 1)

/// @def REALIGN(a,b)
/// @brief True if a and b land in different aligned capacity buckets.
#define REALIGN(a, b) BIT_ALIGN((a)) != BIT_ALIGN((b))

#ifdef _WIN32
#define POPEN _popen
#define PCLOSE _pclose
#define FILENO _fileno
#define FTRUNCATE _chsize
#define WB "wb"
#else
#define POPEN popen
#define PCLOSE pclose
#define FILENO fileno
#define FTRUNCATE ftruncate
#define WB "w"
#endif
long read_be_int(const unsigned char *p, int width);
