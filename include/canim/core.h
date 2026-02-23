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
