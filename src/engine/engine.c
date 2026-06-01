#include "canim/engine.h"
#include "canim/data.h"
#include "canim/log.h"
#include <stdlib.h>

CANIM_API CanimContext *canim_init(CanimLogger *c_log) {
  CanimContext *ctx = calloc(1, sizeof(CanimContext));
  if (!ctx) {
    CANIM_LOG_ERROR("Failed to allocate CanimContext");
    return NULL;
  }

  ctx->data = NULL;

  ctx->node = calloc(1, sizeof(CanimDA));
  if (!ctx->node) {
    CANIM_LOG_ERROR("Failed to allocate node array");
    free(ctx);
    return NULL;
  }

  ctx->target = calloc(1, sizeof(CanimDA));
  if (!ctx->target) {
    CANIM_LOG_ERROR("Failed to allocate target array");
    free(ctx->node);
    free(ctx);
    return NULL;
  }

  *ctx->node = CANIM_DA_INIT(CanimNode);
  *ctx->target = CANIM_DA_INIT(CanimTarget);
  ctx->seed = 88172645463325252ULL;

  return ctx;
}
CANIM_API CanimUID canim_new_uid(CanimContext *ctx) {
  if (!ctx) {
    return 0;
  }

  if (ctx->seed == 0) {
    ctx->seed = 88172645463325252ULL;
  }

  uint64_t x = ctx->seed;

  x ^= x >> 12;
  x ^= x << 25;
  x ^= x >> 27;

  ctx->seed = x;

  return x * 2685821657736338717ULL;
}

CANIM_API CanimTarget *canim_create_and_add_target(CanimLogger *c_log,
                                                   void (*func)(void *,
                                                                CanimNodeList),
                                                   CanimContext *ctx) {
  if (!ctx) {
    CANIM_LOG_ERROR("ctx is NULL");
    return NULL;
  }

  if (!func) {
    CANIM_LOG_ERROR("target function is NULL");
    return NULL;
  }

  CanimTarget target = {0};

  target.mail = calloc(1, sizeof(CanimDA));
  if (!target.mail) {
    CANIM_LOG_ERROR("Failed to allocate mailbox");
    return NULL;
  }
  *target.mail = CANIM_DA_INIT(CanimMsg);

  target.deps = calloc(1, sizeof(CanimDA));
  if (!target.deps) {
    CANIM_LOG_ERROR("Failed to allocate dep list");
    free(target.mail);
    return NULL;
  }
  *target.deps = CANIM_DA_INIT(CanimUID);

  target.uid = canim_new_uid(ctx);
  target.active = false;
  target.frame_buffer = NULL;
  target.full_buffer = NULL;
  target.handle_frame = func;

  CANIM_DA_PUSH(ctx->target, target);

  return (CanimTarget *)ctx->target->start + ctx->target->length - 1;
}

CANIM_API void canim_generate_frame_data(CanimLogger *c_log,
                                         CanimContext *ctx) {}
