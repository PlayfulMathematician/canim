#include "canim/data.h"
#include "canim/log.h"
#include <stdint.h>
#include <stdlib.h>

CANIM_API CanimDA canim_da_new(uint64_t element_size) {
  CanimDA da = {0};
  da.start = NULL;
  da.element_size = element_size;
  da.capacity = 0;
  da.length = 0;

  return da;
}

CANIM_API void canim_da_free(CanimDA *da) {
  if (!da) {
    return;
  }

  free(da->start);

  da->start = NULL;
  da->element_size = 0;
  da->capacity = 0;
  da->length = 0;
}

CANIM_API void canim_da_reserve_capacity(CanimLogger *c_log, CanimDA *da,
                                         uint64_t new_capacity) {
  if (!da) {
    return;
  }
  if (new_capacity <= da->capacity) {
    return;
  }

  uint64_t new_size = new_capacity * da->element_size;

  void *new_start = realloc(da->start, new_size);
  if (!new_start) {
    CANIM_LOG_ERROR(
        "Reallocating array size failed, attempted to go from %zu to %zu",
        da->capacity, new_capacity);
    return;
  }

  da->start = new_start;
  da->capacity = new_capacity;
}

CANIM_API void canim_da_shrink_to_fit(CanimDA *da) {
  if (!da)
    return;

  if (da->length == 0) {
    free(da->start);
    da->start = NULL;
    da->capacity = 0;
    return;
  }

  if (da->length == da->capacity)
    return;
  uint64_t new_size = da->length * da->element_size;
  void *new_start = realloc(da->start, new_size);
  da->start = new_start;
  da->capacity = da->length;
}
