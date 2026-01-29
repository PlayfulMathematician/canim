// SPDX-License-Identifier: MIT
#include "canim/core.h"
#include <stdint.h>
#include <string.h>

#if defined(CANIM_COMPILER_CLANG) || defined(CANIM_COMPILER_GCC)
#define CANIM_BSWAP16 __builtin_bswap16
#define CANIM_BSWAP32 __builtin_bswap32
#define CANIM_BSWAP64 __builtin_bswap64
#else
static inline CanimU16 CANIM_BSWAP16(CanimU16 x) {
  return (CanimU16)((x << 8) | (x >> 8));
}

static inline CanimU32 CANIM_BSWAP32(CanimU32 x) {
  return ((x & 0x000000FFu) << 24) | ((x & 0x0000FF00u) << 8) |
         ((x & 0x00FF0000u) >> 8) | ((x & 0xFF000000u) >> 24);
}

static inline CanimU64 CANIM_BSWAP64(CanimU64 x) {
  return ((x & 0x00000000000000FFull) << 56) |
         ((x & 0x000000000000FF00ull) << 40) |
         ((x & 0x0000000000FF0000ull) << 24) |
         ((x & 0x00000000FF000000ull) << 8) |
         ((x & 0x000000FF00000000ull) >> 8) |
         ((x & 0x0000FF0000000000ull) >> 24) |
         ((x & 0x00FF000000000000ull) >> 40) |
         ((x & 0xFF00000000000000ull) >> 56);
}
#endif

CANIM_API CanimU16 canim_read_be_u16(const CanimByte *p) {
  CanimU16 x;
  memcpy(&x, p, sizeof x);
#if CANIM_CPU_LE
  return CANIM_BSWAP16(x);
#else
  return x;
#endif
}

CANIM_API CanimU16 canim_read_le_u16(const CanimByte *p) {
  CanimU16 x;
  memcpy(&x, p, sizeof x);
#if CANIM_CPU_LE
  return x;
#else
  return CANIM_BSWAP16(x);
#endif
}

CANIM_API CanimU32 canim_read_be_u32(const CanimByte *p) {
  CanimU32 x;
  memcpy(&x, p, sizeof x);
#if CANIM_CPU_LE
  return CANIM_BSWAP32(x);
#else
  return x;
#endif
}

CANIM_API CanimU32 canim_read_le_u32(const CanimByte *p) {
  CanimU32 x;
  memcpy(&x, p, sizeof x);
#if CANIM_CPU_LE
  return x;
#else
  return CANIM_BSWAP32(x);
#endif
}

CANIM_API CanimU64 canim_read_be_u64(const CanimByte *p) {
  CanimU64 x;
  memcpy(&x, p, sizeof x);
#if CANIM_CPU_LE
  return CANIM_BSWAP64(x);
#else
  return x;
#endif
}

CANIM_API CanimU64 canim_read_le_u64(const CanimByte *p) {
  CanimU64 x;
  memcpy(&x, p, sizeof x);
#if CANIM_CPU_LE
  return x;
#else
  return CANIM_BSWAP64(x);
#endif
}

CANIM_API CanimFloat canim_read_be_f32(const CanimByte *p) {
  CanimU32 u = canim_read_be_u32(p);
  CanimFloat f;
  memcpy(&f, &u, sizeof(f));
  return f;
}

CANIM_API CanimFloat canim_read_le_f32(const CanimByte *p) {
  CanimU32 u = canim_read_le_u32(p);
  CanimFloat f;
  memcpy(&f, &u, sizeof(f));
  return f;
}

CANIM_API CanimDouble canim_read_be_f64(const CanimByte *p) {
  CanimU64 u = canim_read_be_u64(p);
  CanimDouble d;
  memcpy(&d, &u, sizeof(d));
  return d;
}

CANIM_API CanimDouble canim_read_le_f64(const CanimByte *p) {
  CanimU64 u = canim_read_le_u64(p);
  CanimDouble d;
  memcpy(&d, &u, sizeof(d));
  return d;
}
