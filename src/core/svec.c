// SPDX-License-Identifier: MIT
#include "canim/core.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static inline void svec_init(CanimResult *result, SVec *v, size_t elem_size) {
  if (elem_size == 0) {
    *result = SVEC_ZERO_ELEMENT_SIZE;
    return;
  }
  v->element_size = elem_size;
  v->list_size = 0;
  v->data = NULL;
  *result = SUCCESS;
}

static inline void svec_free(CanimResult *result, SVec *v) {
  free(v->data);
  v->data = NULL;
  v->list_size = 0;

  *result = SUCCESS;
}

static inline void svec_push(CanimResult *result, SVec *v, const void *elem) {

  size_t old_size = v->list_size;
  size_t new_size = old_size + 1;

  if (REALIGN(old_size, new_size)) {
    size_t new_cap = BIT_ALIGN(new_size);
    void *new_data = realloc(v->data, new_cap * v->element_size);

    if (!new_data) {
      *result = SVEC_REALLOC_FAIL;
      return;
    }
    v->data = new_data;
  }

  memcpy(v->data + old_size * v->element_size, elem, v->element_size);
  v->list_size++;

  *result = SUCCESS;
}

static inline void svec_pop(CanimResult *result, SVec *v, void *out) {
  size_t old_size = v->list_size;
  size_t new_size = old_size - 1;
  if (out) {
    memcpy(out, v->data + (old_size - 1) * v->element_size, v->element_size);
  }
  if (REALIGN(old_size, new_size)) {
    size_t new_cap = BIT_ALIGN(new_size);
    void *new_data = realloc(v->data, new_cap * v->element_size);

    if (!new_data) {
      *result = SVEC_REALLOC_FAIL;
      return;
    }
    v->data = new_data;
  }
  v->list_size--;
  *result = SUCCESS;
}

static inline void svec_set(CanimResult *result, SVec *v, size_t i,
                            const void *elem) {
  memcpy(v->data + i * v->element_size, elem, v->element_size);
  *result = SUCCESS;
}

static inline void *svec_get(CanimResult *result, SVec *v, size_t i) {
  *result = SUCCESS;
  return v->data + i * v->element_size;
}
