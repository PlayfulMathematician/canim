#pragma once
#include "core.h"
#include <stddef.h>
#include <stdint.h>
typedef struct {
  uint8_t *base;
  size_t size;
  size_t head;
} CanimArena;
CANIM_API void *canim_arena_alloc(CanimArena *a, size_t size, size_t align);
CANIM_API void canim_arena_init(CanimArena *a, size_t size);
CANIM_API void canim_arena_free(CanimArena *a);
CANIM_API void *canim_arena_alloc(CanimArena *a, size_t size, size_t align);
CANIM_API void canim_arena_reset(CanimArena *a);
CANIM_API size_t canim_arena_mark(CanimArena *a);
CANIM_API void canim_arena_reset_to(CanimArena *a, size_t mark);
