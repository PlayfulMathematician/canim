#include "canim/arena.h"
#include <stdlib.h>

static size_t align_up(size_t x, size_t align) {
  return (x + (align - 1)) & ~(align - 1);
}

CANIM_API void canim_arena_init(CanimArena *a, size_t size) {
  a->base = (uint8_t *)malloc(size);
  a->size = size;
  a->head = 0;
}

CANIM_API void canim_arena_free(CanimArena *a) {
  free(a->base);
  a->base = NULL;
  a->size = 0;
  a->head = 0;
}

CANIM_API void *canim_arena_alloc(CanimArena *a, size_t size, size_t align) {
  size_t p = align_up(a->head, align);
  if (p + size > a->size) {
    return NULL;
  }
  void *result = a->base + p;
  a->head = p + size;
  return result;
}

CANIM_API void canim_arena_reset(CanimArena *a) { a->head = 0; }

CANIM_API size_t canim_arena_mark(CanimArena *a) { return a->head; }

CANIM_API void canim_arena_reset_to(CanimArena *a, size_t mark) {
  a->head = mark;
}
