#ifndef CANIM_SHARED_H
#define CANIM_SHARED_H
#include <stdint.h>
#define CANIM_API __attribute__((visibility("default")))
typedef uint32_t CanimResult;

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
#ifndef CANIM_PLATFORM_KNOWN
#define CANIM_PLATFORM_UNKNOWN
#endif
#endif
