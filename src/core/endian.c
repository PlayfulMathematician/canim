// SPDX-License-Identifier: MIT
#include "canim/core.h"
#include <stdint.h>
#include <string.h>

static inline uint16_t read_be_u16(const unsigned char *p) {
  return ((uint16_t)p[0] << 010) | ((uint16_t)p[1] << 000);
}

static inline uint32_t read_be_u32(const unsigned char *p) {
  return ((uint32_t)p[0] << 030) | ((uint32_t)p[1] << 020) |
         ((uint32_t)p[2] << 010) | ((uint32_t)p[3] << 000);
}

static inline uint64_t read_be_u64(const unsigned char *p) {
  return ((uint64_t)p[0] << 070) | ((uint64_t)p[1] << 060) |
         ((uint64_t)p[2] << 050) | ((uint64_t)p[3] << 040) |
         ((uint64_t)p[4] << 030) | ((uint64_t)p[5] << 020) |
         ((uint64_t)p[6] << 010) | ((uint64_t)p[7] << 000);
}

static inline uint16_t read_le_u16(const unsigned char *p) {
  return ((uint16_t)p[1] << 010) | ((uint16_t)p[0] << 000);
}

static inline uint32_t read_le_u32(const unsigned char *p) {
  return ((uint32_t)p[3] << 030) | ((uint32_t)p[2] << 020) |
         ((uint32_t)p[1] << 010) | ((uint32_t)p[0] << 000);
}

static inline uint64_t read_le_u64(const unsigned char *p) {
  return ((uint64_t)p[7] << 070) | ((uint64_t)p[6] << 060) |
         ((uint64_t)p[5] << 050) | ((uint64_t)p[4] << 040) |
         ((uint64_t)p[3] << 030) | ((uint64_t)p[2] << 020) |
         ((uint64_t)p[1] << 010) | ((uint64_t)p[0] << 000);
}

static inline void write_be_u16(unsigned char *p, uint16_t v) {
  p[0] = (unsigned char)(v >> 010);
  p[1] = (unsigned char)(v >> 000);
}

static inline void write_be_u32(unsigned char *p, uint32_t v) {
  p[0] = (unsigned char)(v >> 030);
  p[1] = (unsigned char)(v >> 020);
  p[2] = (unsigned char)(v >> 010);
  p[3] = (unsigned char)(v >> 000);
}

static inline void write_be_u64(unsigned char *p, uint64_t v) {
  p[0] = (unsigned char)(v >> 070);
  p[1] = (unsigned char)(v >> 060);
  p[2] = (unsigned char)(v >> 050);
  p[3] = (unsigned char)(v >> 040);
  p[4] = (unsigned char)(v >> 030);
  p[5] = (unsigned char)(v >> 020);
  p[6] = (unsigned char)(v >> 010);
  p[7] = (unsigned char)(v >> 000);
}

static inline void write_le_u16(unsigned char *p, uint16_t v) {
  p[0] = (unsigned char)(v >> 000);
  p[1] = (unsigned char)(v >> 010);
}

static inline void write_le_u32(unsigned char *p, uint32_t v) {
  p[0] = (unsigned char)(v >> 000);
  p[1] = (unsigned char)(v >> 010);
  p[2] = (unsigned char)(v >> 020);
  p[3] = (unsigned char)(v >> 030);
}

static inline void write_le_u64(unsigned char *p, uint64_t v) {
  p[0] = (unsigned char)(v >> 000);
  p[1] = (unsigned char)(v >> 010);
  p[2] = (unsigned char)(v >> 020);
  p[3] = (unsigned char)(v >> 030);
  p[4] = (unsigned char)(v >> 040);
  p[5] = (unsigned char)(v >> 050);
  p[6] = (unsigned char)(v >> 060);
  p[7] = (unsigned char)(v >> 070);
}

static inline float read_be_f32(const unsigned char *p) {
  uint32_t u = read_be_u32(p);
  float f;
  memcpy(&f, &u, sizeof(f));
  return f;
}

static inline float read_le_f32(const unsigned char *p) {
  uint32_t u = read_le_u32(p);
  float f;
  memcpy(&f, &u, sizeof(f));
  return f;
}

static inline void write_be_f32(unsigned char *p, float f) {
  uint32_t u;
  memcpy(&u, &f, sizeof(u));
  write_be_u32(p, u);
}

static inline void write_le_f32(unsigned char *p, float f) {
  uint32_t u;
  memcpy(&u, &f, sizeof(u));
  write_le_u32(p, u);
}

static inline double read_be_f64(const unsigned char *p) {
  uint64_t u = read_be_u64(p);
  double d;
  memcpy(&d, &u, sizeof(d));
  return d;
}

static inline double read_le_f64(const unsigned char *p) {
  uint64_t u = read_le_u64(p);
  double d;
  memcpy(&d, &u, sizeof(d));
  return d;
}

static inline void write_be_f64(unsigned char *p, double d) {
  uint64_t u;
  memcpy(&u, &d, sizeof(u));
  write_be_u64(p, u);
}

static inline void write_le_f64(unsigned char *p, double d) {
  uint64_t u;
  memcpy(&u, &d, sizeof(u));
  write_le_u64(p, u);
}
