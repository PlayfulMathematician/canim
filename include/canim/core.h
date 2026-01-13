// SPDX-License-Identifier: AGPL-3.0
#pragma once
/// @file core.h
/// @brief This is everything core to Canim that is shared between subsystems
#include <stdint.h>
#include <sys/types.h>
#if defined(_WIN32) || defined(_WIN64)
#define CANIM_PLATFORM_WINDOWS 1
#elif defined(__APPLE__) && defined(__MACH__)
#define CANIM_PLATFORM_MACOS 1
#elif defined(__linux__)
#define CANIM_PLATFORM_LINUX 1
#else
#error "Unsupported platform for Canim"
#endif

#if defined(CANIM_PLATFORM_LINUX) || defined(CANIM_PLATFORM_MACOS)
#define CANIM_POSIX 1
#endif

#if defined(__x86_64__) || defined(_M_X64)
#define CANIM_ARCH_X86_64 1
#elif defined(__aarch64__) || defined(_M_ARM64)
#define CANIM_ARCH_ARM64 1
#else
#define CANIM_ARCH_UNKNOWN 1
#endif

#if defined(__clang__)
#define CANIM_COMPILER_CLANG 1
#elif defined(__GNUC__)
#define CANIM_COMPILER_GCC 1
#elif defined(_MSC_VER)
#define CANIM_COMPILER_MSVC 1
#else
#error "Unsupported compiler for Canim"
#endif

#if !defined(CANIM_DEBUG) && !defined(CANIM_RELEASE)
#error "Build mode not defined (CANIM_DEBUG or CANIM_RELEASE)"
#endif

#if defined(CANIM_DEBUG) && defined(CANIM_RELEASE)
#error "Both CANIM_DEBUG and CANIM_RELEASE are defined"
#endif
#if defined(CANIM_PLATFORM_WINDOWS)
#if defined(CANIM_BUILD_DLL)
#define CANIM_API __declspec(dllexport)
#elif defined(CANIM_USE_DLL)
#define CANIM_API __declspec(dllimport)
#else
#define CANIM_API
#endif
#else
#define CANIM_API __attribute__((visibility("default")))
#endif

#if defined(CANIM_COMPILER_MSVC)
#define CANIM_FORCE_INLINE __forceinline
#define CANIM_NO_INLINE __declspec(noinline)
#elif defined(CANIM_COMPILER_GCC) || defined(CANIM_COMPILER_CLANG)
#define CANIM_FORCE_INLINE inline __attribute__((always_inline))
#define CANIM_NO_INLINE __attribute__((noinline))
#else
#define CANIM_FORCE_INLINE inline
#define CANIM_NO_INLINE
#endif

#if !defined(__STDC_VERSION__) || (__STDC_VERSION__ < 201112L)
#error "Canim requires C11 or newer"
#endif

#if defined(CANIM_COMPILER_GCC) || defined(CANIM_COMPILER_CLANG)
#define CANIM_LIKELY(x) __builtin_expect(!!(x), 1)
#define CANIM_UNLIKELY(x) __builtin_expect(!!(x), 0)
#else
#define CANIM_LIKELY(x) (x)
#define CANIM_UNLIKELY(x) (x)
#endif

#define CANIM_UNUSED(x) ((void)(x))
#if defined(CANIM_COMPILER_MSVC)
#define CANIM_ALIGN(n) __declspec(align(n))
#else
#define CANIM_ALIGN(n) __attribute__((aligned(n)))
#endif
/// @def CANIM_CPU_LE
/// @brief Indicates whether the CPU is little endian
#if defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__)
#define CANIM_CPU_LE (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
#elif defined(CANIM_PLATFORM_WINDOWS)
#define CANIM_CPU_LE 1
#else
#error "Cannot determine cpu endianness"
#endif
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
  REALLOC_FAIL,           ///< When using realloc, a failure occurred
  FSEEK_FAILURE,          ///< When using fseek, a failure occurred,
  FTELL_FAILURE,          ///< When using ftell, a failure occured
  MALLOC_FAIL,            ///< When using malloc, a failure occurred
};

/// @brief Result code used across Canim operations.
typedef uint32_t CanimResult;

/// @brief Print out the error
/// @param error The error to be printed.
void print_error(CanimResult error);

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

/// @brief Read a 16-bit unsigned integer in big endian byte order
/// @param p Pointer to a buffer containing at least 2 bytes
/// @return The 16-bit unsigned integer
CANIM_API uint16_t canim_read_be_u16(const unsigned char *p);

/// @brief Read a 32-bit unsigned integer in big endian byte order
/// @param p Pointer to a buffer containing at least 4 bytes
/// @return The 32-bit unsigned integer
CANIM_API uint32_t canim_read_be_u32(const unsigned char *p);

/// @brief Read a 64-bit unsigned integer in big endian byte order
/// @param p Pointer to a buffer containing at least 8 bytes
/// @return The 64-bit unsigned integer
CANIM_API uint64_t canim_read_be_u64(const unsigned char *p);

/// @brief Read a 16-bit unsigned integer in little endian byte order
/// @param p Pointer to a buffer containing at least 2 bytes
/// @return The 16-bit unsigned integer
CANIM_API uint16_t canim_read_le_u16(const unsigned char *p);

/// @brief Read a 32-bit unsigned integer in little endian byte order
/// @param p Pointer to a buffer containing at least 4 bytes
/// @return The 32-bit unsigned integer
CANIM_API uint32_t canim_read_le_u32(const unsigned char *p);

/// @brief Read a 64-bit unsigned integer in little endian byte order
/// @param p Pointer to a buffer containing at least 8 bytes
/// @return The 64-bit unsigned integer
CANIM_API uint64_t canim_read_le_u64(const unsigned char *p);

/// @brief Read a 32-bit float in big endian byte order
/// @param p The buffer to be read
/// @return The float
CANIM_API float canim_read_be_f32(const unsigned char *p);

/// @brief Read a 64-bit float in big endian byte order
/// @param p The buffer to be read
/// @return The float
CANIM_API double canim_read_be_f64(const unsigned char *p);

/// @brief Read a 32-bit float in little endian byte order
/// @param p The buffer to be read
/// @return The float
CANIM_API float canim_read_le_f32(const unsigned char *p);

/// @brief Read a 64-bit float in little endian byte order
/// @param p The buffer to be read
/// @return The float
CANIM_API double canim_read_le_f64(const unsigned char *p);

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
