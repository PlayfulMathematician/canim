// SPDX-License-Identifier: MIT
#pragma once

/// @file core.h
/// @brief This is everything core to Canim that is shared between subsystems

#include <stdint.h>
#include <sys/types.h>
/// @def CANIM_API
/// @brief Meant for a visibility label to all parts of the Canim API
#define CANIM_API __attribute__((visibility("default")))

/// @def STATUS_TYPE_SHIFT
/// @brief The bit shift applied to the value of an error to get it's type
#define STATUS_TYPE_SHIFT 24

/// @def STATUS_TYPE_MASK
/// @brief The mask applied to the an error to eliminate it's subtype.
#define STATUS_TYPE_MASK 0xFF000000

/// @def SUCCESS
/// @brief This is the status code for success
#define SUCCESS 0x00

/// @def NOOP
/// @brief No operation performed.
#define NOOP 0x01

/// @def NONFATAL
/// @brief Non-fatal error (unused)
#define NONFATAL 0x02

/// @def FATAL
/// @brief Fatal error.
#define FATAL 0x03

/// @def STATUS_TYPE
/// @brief Extracts the status type (SUCCESS/NOOP/NONFATAL/FATAL).
#define STATUS_TYPE(code) (((code) & STATUS_TYPE_MASK) >> STATUS_TYPE_SHIFT)

/// @def IS_AN_ERROR
/// @brief True if code is an error (NONFATAL or FATAL).
#define IS_AN_ERROR(x)                                                         \
  ((STATUS_TYPE((x)) == FATAL) || (STATUS_TYPE((x)) == NONFATAL))

/// @brief This are all of the error codes
enum {
  GFX_DEVICE_CALLOC_ERROR =
      (uint32_t)0x03000000, ///< When using calloc to allocate memory for a
                            ///< GfxDevice, calloc failed
  EGL_NO_DISPLAY_ERROR,     ///< When creating an EGL display, no display was
                            ///< created
  EGL_DISPLAY_INIT_ERROR, ///< When initializing an EGL display something failed
  EGL_DISPLAY_CONFIGURATION_ERROR, ///< When configuring an EGL display
                                   ///< something failed.
  EGL_NO_SURFACE_ERROR,      ///< When creating an EGL surface, no surface was
                             ///< created
  EGL_NO_CONTEXT_ERROR,      ///< When creating an EGL context, no context was
                             ///< created.
  EGL_MAKE_CURRENT_ERROR,    ///< When the making the EGL context, surface and
                             ///< display the current one, something failed.
  SDL_INIT_VIDEO_ERROR,      ///< When initializing SDL video, something failed
  SDL_WINDOW_CREATION_ERROR, ///< When making a window with SDL2, something
                             ///< failed
  SDL_GL_CONTEXT_CREATION_ERROR, ///< When making an OpenGL context with SDL,
                                 ///< something failed.
  SDL_GLAD_LOAD_ERROR, ///< When loading OpenGL functions with GLAD, using SDL,
                       ///< something failed
  EGL_GLAD_LOAD_ERROR, ///< When loading OpenGL functions with GLAD, using EGL,
                       ///< something failed
  SVEC_ZERO_ELEMENT_SIZE, ///< When initializing an SVec, the element size was
                          ///< set to zero
  SVEC_REALLOC_FAIL ///< When reallocating space for an SVec, something failed
};

/// @brief Result code used across Canim operations.
typedef uint32_t CanimResult;

/// @brief Print out the error
/// @param error The error to be printed.
void print_error(CanimResult error);

/// @def CANIM_PLATFORM_WINDOWS
/// @brief Defined on Windows (_WIN32).
#ifdef _WIN32
#define CANIM_PLATFORM_WINDOWS 1
#define CANIM_PLATFORM_KNOWN 1
#endif

/// @def CANIM_PLATFORM_MAC
/// @brief Defined on macOS (__APPLE__).
#ifdef __APPLE__
#define CANIM_PLATFORM_MAC 1
#define CANIM_PLATFORM_KNOWN 1
#endif

/// @def CANIM_PLATFORM_LINUX
/// @brief Defined on Linux (__linux__).
#ifdef __linux__
#define CANIM_PLATFORM_LINUX 1
#define CANIM_PLATFORM_KNOWN 1
#endif

/// @def CANIM_PLATFORM_POSIX
/// @brief Defined on POSIX platforms (macOS or Linux).
#if defined(CANIM_PLATFORM_LINUX) || defined(CANIM_PLATFORM_MAC)
#define CANIM_PLATFORM_POSIX 1
#define CANIM_PLATFORM_KNOWN 1
#endif

/// @def CANIM_PLATFORM_UNKNOWN
/// @brief Defined if no known platform could be detected.
#ifndef CANIM_PLATFORM_KNOWN
#define CANIM_PLATFORM_UNKNOWN 1
#endif

/// @def max
/// @brief A max macro
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

/// @def POPEN
/// @brief A cross platform alias for opening a pipe.
#ifdef CANIM_PLATFORM_WINDOWS
#define POPEN _popen
#else
#define POPEN popen
#endif

/// @def PCLOSE
/// @brief A cross platform alias for closing a pipe.
#ifdef CANIM_PLATFORM_WINDOWS
#define PCLOSE _pclose
#else
#define PCLOSE pclose
#endif

/// @def WB
/// @brief Correct mode for writing in binary files on each platform
#ifdef CANIM_PLATFORM_WINDOWS
#define WB "wb"
#else
#define WB "w"
#endif

/// @brief Read a 16-bit unsigned integer in big endian byte order
/// @param p Pointer to a buffer containing at least 2 bytes
/// @return The 16-bit unsigned integer
static inline uint16_t read_be_u16(const unsigned char *p);

/// @brief Read a 32-bit unsigned integer in big endian byte order
/// @param p Pointer to a buffer containing at least 4 bytes
/// @return The 32-bit unsigned integer
static inline uint32_t read_be_u32(const unsigned char *p);

/// @brief Read a 64-bit unsigned integer in big endian byte order
/// @param p Pointer to a buffer containing at least 8 bytes
/// @return The 64-bit unsigned integer
static inline uint64_t read_be_u64(const unsigned char *p);

/// @brief Read a 16-bit unsigned integer in little endian byte order
/// @param p Pointer to a buffer containing at least 2 bytes
/// @return The 16-bit unsigned integer
static inline uint16_t read_le_u16(const unsigned char *p);

/// @brief Read a 32-bit unsigned integer in little endian byte order
/// @param p Pointer to a buffer containing at least 4 bytes
/// @return The 32-bit unsigned integer
static inline uint32_t read_le_u32(const unsigned char *p);

/// @brief Read a 64-bit unsigned integer in little endian byte order
/// @param p Pointer to a buffer containing at least 8 bytes
/// @return The 64-bit unsigned integer
static inline uint64_t read_le_u64(const unsigned char *p);

/// @brief Write a 16-bit unsigned integer in big endian byte order
/// @param p The buffer to be written to
/// @param v The integer to be converted
static inline void write_be_u16(unsigned char *p, uint16_t v);

/// @brief Write a 32-bit unsigned integer in big endian byte order
/// @param p The buffer to be written to
/// @param v The integer to be converted
static inline void write_be_u32(unsigned char *p, uint32_t v);

/// @brief Write a 64-bit unsigned integer in big endian byte order
/// @param p The buffer to be written to
/// @param v The integer to be converted
static inline void write_be_u64(unsigned char *p, uint64_t v);

/// @brief Write a 16-bit unsigned integer in little endian byte order
/// @param p The buffer to be written to
/// @param v The integer to be converted
static inline void write_le_u16(unsigned char *p, uint16_t v);

/// @brief Write a 32-bit unsigned integer in little endian byte order
/// @param p The buffer to be written to
/// @param v The integer to be converted
static inline void write_le_u32(unsigned char *p, uint32_t v);

/// @brief Write a 64-bit unsigned integer in little endian byte order
/// @param p The buffer to be written to
/// @param v The integer to be converted
static inline void write_le_u64(unsigned char *p, uint64_t v);

/// @brief Read a 32-bit float in big endian byte order
/// @param p The buffer to be read
/// @return The float
static inline float read_be_f32(const unsigned char *p);

/// @brief Read a 64-bit float in big endian byte order
/// @param p The buffer to be read
/// @return The float
static inline double read_be_f64(const unsigned char *p);

/// @brief Read a 32-bit float in little endian byte order
/// @param p The buffer to be read
/// @return The float
static inline float read_le_f32(const unsigned char *p);

/// @brief Read a 64-bit float in little endian byte order
/// @param p The buffer to be read
/// @return The float
static inline double read_le_f64(const unsigned char *p);

/// @brief Write a 32 bit float to a big endian buffer
/// @param The buffer to be written to
/// @param f The float
static inline void write_be_f32(unsigned char *p, float f);

/// @brief Write a 64 bit ouble to a big endian buffer
/// @param The buffer to be written to
/// @param f The double
static inline void write_be_f64(unsigned char *p, double f);

/// @brief Write a 32 bit float to a little endian buffer
/// @param The buffer to be written to
/// @param f The float
static inline void write_le_f32(unsigned char *p, float f);

/// @brief Write a 64 bit ouble to a little endian buffer
/// @param The buffer to be written to
/// @param f The double
static inline void write_le_f64(unsigned char *p, double f);

/// @def BIT_IGNORE
/// @brief Alignment granularity in bits (round up to 2^BIT_IGNORE).
#define BIT_IGNORE 4

/// @def BIT_SIZE
/// @brief 2^BIT_IGNORE - 1
#define BIT_SIZE ((1u << BIT_IGNORE) - 1u)

/// @def BIT_ALIGN(x)
/// @brief Round x up to nearest aligned multiple of 2^BIT_IGNORE. Always
#define BIT_ALIGN(x)                                                           \
  (((((x) + BIT_SIZE) & ~BIT_SIZE)) ? (((x) + BIT_SIZE) & ~BIT_SIZE) : 1)

/// @def REALIGN(a, b)
/// @brief True if a and b land in different aligned capacity buckets.
#define REALIGN(a, b) (BIT_ALIGN(a) != BIT_ALIGN(b))

/// @struct SVec
/// @brief Minimal growable byte-vector.
typedef struct {
  size_t element_size; ///< Size of each element in bytes.
  size_t list_size;    ///< Number of elements stored.
  unsigned char *data; ///< Contiguous raw byte storage
} SVec;

/// @brief Initialize a vector with a fixed element size.
/// @param[out] result A status code
/// @param v Pointer to SVec
/// @param elem_size Number of bytes per element
static inline void svec_init(CanimResult *result, SVec *v, size_t elem_size);

/// @brief Free all memory owned by the vector.
/// @param[out] result A status code
/// @param v Pointer to SVec
static inline void svec_free(CanimResult *result, SVec *v);

/// @brief Append one element, reallocating only when bucket changes.
/// @param[out] result A status code
/// @param v Pointer to SVec
/// @param elem Pointer to element data
static inline void svec_push(CanimResult *result, SVec *v, const void *elem);

/// @brief Remove the last element, shrinking bucket only if needed.
/// @param[out] result A status code
/// @param v Pointer to SVec
/// @param out Optional output location
static inline void svec_pop(CanimResult *result, SVec *v, void *out);

/// @brief Get a pointer to element at index i
/// @param[out] result A status code
/// @param v Pointer to SVec
/// @param i Index to read from
/// @return A pointer to the element
static inline void *svec_get(CanimResult *result, SVec *v, size_t i);

/// @brief Set the element at index i to the value pointed to by elem.
/// @param[out] result A status code
/// @param v Pointer to SVec
/// @param i Index to write to
/// @param elem Pointer to source data
static inline void svec_set(CanimResult *result, SVec *v, size_t i,
                            const void *elem);
