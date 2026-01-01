#pragma once
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
