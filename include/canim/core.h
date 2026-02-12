// SPDX-License-Identifier: GPL-3.0
#pragma once
/// @file core.h
/// @brief This is everything core to Canim that is shared between subsystems
#include <stdbool.h>
#include <stdint.h>
#include <sys/types.h>
#include <wchar.h>
#if defined(_WIN32) || defined(_WIN64)
#define CANIM_PLATFORM_WINDOWS 1
#elif defined(__APPLE__) && defined(__MACH__)
#define CANIM_PLATFORM_MACOS 1
#elif defined(__linux__)
#define CANIM_PLATFORM_LINUX 1
#else
#error "Unsupported platform for Canim"
#endif

#ifdef CANIM_PLATFORM_WINDOWS
#error "I do not want to support windows"
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

typedef double CanimNumber;
typedef unsigned char CanimByte;
typedef uint8_t CanimU8;
typedef uint16_t CanimU16;
typedef uint32_t CanimU32;
typedef uint64_t CanimU64;
typedef int8_t CanimS8;
typedef int16_t CanimS16;
typedef int32_t CanimS32;
typedef int64_t CanimS64;
typedef double CanimDouble;
typedef float CanimFloat;

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
/// @brief Result code used across Canim operations.
typedef uint32_t CanimResultCode;

/// @brief The status of the result
typedef uint32_t CanimResultStatus;
/// @brief Additional info about the result
typedef char *CanimResultAdditionalInfo;
/// @brief The line number
typedef int CanimResultLine;
/// @brief This where the result occured
typedef char *CanimResultFile;
typedef struct {
  CanimResultCode code;
  CanimResultStatus status;
  CanimResultAdditionalInfo additional_info;
  CanimResultLine line;
  CanimResultFile file;
} CanimResult;

/// @brief These are all the result statuses
enum {
  CANIM_RESULT_STATUS_SUCCESS =
      (CanimResultStatus)0, ///< Whenever there is a success
  CANIM_RESULT_STATUS_DEPRECATED,
  CANIM_RESULT_STATUS_TODO,
  CANIM_RESULT_STATUS_UNREACHABLE,
  CANIM_RESULT_STATUS_INCOMPATIBILITY,
  CANIM_RESULT_STATUS_FATAL,
  CANIM_RESULT_STATUS_NOT_FATAL
};

/// @brief These are all the result codes
enum {
  CANIM_RESULT_CODE_OTHER = (CanimResultCode)0xffffffff,
  CANIM_RESULT_CODE_SUCCESS = (CanimResultCode)0,
  CANIM_RESULT_CODE_MEMORY,
  CANIM_RESULT_CODE_MATH,
  CANIM_RESULT_CODE_FILE,
  CANIM_RESULT_CODE_LOADING,
  CANIM_RESULT_CODE_PARSING,
  CANIM_RESULT_CODE_GFX,
};

/// @remark It is important to have your result point be c_result, otherwise I
/// will be sad. And my macros will fail
/// NO MORE MACROS
#define CANIM_RESULT_EXTENDED(code_val, stat, info_str)                        \
  do {                                                                         \
    c_result->code = (code_val);                                               \
    c_result->status = (stat);                                                 \
    c_result->additional_info = (info_str);                                    \
    c_result->line = __LINE__;                                                 \
    c_result->file = __FILE__;                                                 \
  } while (0)
/// @todo Document these macros
#define CANIM_RESULT_SUCCESS()                                                 \
  CANIM_RESULT_EXTENDED(CANIM_RESULT_CODE_SUCCESS,                             \
                        CANIM_RESULT_STATUS_SUCCESS, NULL)
#define CANIM_RESULT_FATAL_EXT(code_val, info_str)                             \
  CANIM_RESULT_EXTENDED(code_val, CANIM_RESULT_STATUS_FATAL, info_str)
#define CANIM_RESULT_FATAL(code_val) CANIM_RESULT_FATAL_EXT(code_val, NULL)
#define CANIM_RESULT_NOT_FATAL_EXT(code_val, info_str)                         \
  CANIM_RESULT_EXTENDED(code_val, CANIM_RESULT_STATUS_NOT_FATAL, info_str)
#define CANIM_RESULT_NOT_FATAL(code_val)                                       \
  CANIM_RESULT_NOT_FATAL_EXT(code_val, NULL)

/// @brief Checks if is error
/// @param The result pointer
/// @return If the result is an error
CANIM_API bool canim_is_error(CanimResult *c_result);
/// @brief Print out the result
/// @param result The result to be printed.
CANIM_API void canim_print_error(CanimResult *c_result);

/// @def max
/// @brief A max macro
#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif

/// @def CANIM_EPSILON
/// @brief Tolerance for floating-point comparisons.
#define CANIM_EPSILON 0.000001

/// @def null
/// @brief I do not want to capitalize NULL
#define null NULL

/// @def BUFFER_SIZE
/// @brief The size of a buffer
#define BUFFER_SIZE 4096

/// @brief Read a 16-bit unsigned integer in big endian byte order
/// @param p Pointer to a buffer containing at least 2 bytes
/// @return The 16-bit unsigned integer
CANIM_API CanimU16 canim_read_be_u16(const CanimByte *p);

/// @brief Read a 32-bit unsigned integer in big endian byte order
/// @param p Pointer to a buffer containing at least 4 bytes
/// @return The 32-bit unsigned integer
CANIM_API CanimU32 canim_read_be_u32(const CanimByte *p);

/// @brief Read a 64-bit unsigned integer in big endian byte order
/// @param p Pointer to a buffer containing at least 8 bytes
/// @return The 64-bit unsigned integer
CANIM_API CanimU64 canim_read_be_u64(const CanimByte *p);

/// @brief Read a 16-bit unsigned integer in little endian byte order
/// @param p Pointer to a buffer containing at least 2 bytes
/// @return The 16-bit unsigned integer
CANIM_API CanimU16 canim_read_le_u16(const CanimByte *p);

/// @brief Read a 32-bit unsigned integer in little endian byte order
/// @param p Pointer to a buffer containing at least 4 bytes
/// @return The 32-bit unsigned integer
CANIM_API CanimU32 canim_read_le_u32(const CanimByte *p);

/// @brief Read a 64-bit unsigned integer in little endian byte order
/// @param p Pointer to a buffer containing at least 8 bytes
/// @return The 64-bit unsigned integer
CANIM_API CanimU64 canim_read_le_u64(const CanimByte *p);

/// @brief Read a 32-bit float in big endian byte order
/// @param p The buffer to be read
/// @return The float
CANIM_API CanimFloat canim_read_be_f32(const CanimByte *p);

/// @brief Read a 64-bit float in big endian byte order
/// @param p The buffer to be read
/// @return The float
CANIM_API CanimDouble canim_read_be_f64(const CanimByte *p);

/// @brief Read a 32-bit float in little endian byte order
/// @param p The buffer to be read
/// @return The float
CANIM_API CanimFloat canim_read_le_f32(const CanimByte *p);

/// @brief Read a 64-bit float in little endian byte order
/// @param p The buffer to be read
/// @return The float
CANIM_API CanimDouble canim_read_le_f64(const CanimByte *p);

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
