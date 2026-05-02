// SPDX-License-Identifier: GPL-3.0
// @file data.h
// @brief This header handles datatypes

// @todo Document this
#pragma once
#include "canim/core.h"
#include "canim/log.h"
#include <stdint.h>
typedef struct {
  void *start;
  uint64_t element_size;
  uint64_t capacity;
  uint64_t length;
} CanimDA;

#define CANIM_DA_INIT(t) canim_da_new(sizeof(t))
#define CANIM_DA_GET_ELEMENT(da, t, i)                                         \
  ((t *)((uint8_t *)(da).start + (da).element_size * (i)))
#define CANIM_DA_GET(da, t, i) (*CANIM_DA_GET_ELEMENT(da, t, i))
#define CANIM_DA_PUSH(da, element)                                             \
  do {                                                                         \
    if ((da)->length >= (da)->capacity) {                                      \
      canim_da_reserve_capacity(c_log, (da),                                   \
                                (da)->capacity ? (da)->capacity * 2 : 8);      \
    }                                                                          \
    *CANIM_DA_GET_ELEMENT(*(da), typeof(element), (da)->length++) = (element); \
  } while (0)

#define CANIM_DA_POP(da, ptr)                                                  \
  do {                                                                         \
    ptr = (typeof(ptr))((uint8_t *)(da).start +                                \
                        (da).element_size * ((da).length - 1));                \
    (da).length -= 1;                                                          \
  } while (0)

CANIM_API CanimDA canim_da_new(uint64_t element_size);
CANIM_API void canim_da_free(CanimDA *da);
CANIM_API void canim_da_reserve_capacity(CanimLogger *log, CanimDA *da,
                                         uint64_t new_capacity);
CANIM_API void canim_da_shrink_to_fit(CanimDA *da);
