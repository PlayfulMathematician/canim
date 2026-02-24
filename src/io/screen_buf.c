#include "canim/core.h"
#include "canim/io.h"
#include "canim/log.h"
#include <stdlib.h>
CANIM_API CanimScreenBuffer canim_allocate_screen_buffer(CanimLogger *c_log,
                                                         CanimU64 w,
                                                         CanimU64 h) {
  CanimByte *rgb = malloc(w * h * 3);
  if (!rgb) {
    CANIM_LOG_ERROR("Allocating the screen buffer failed");
  }
  CanimScreenBuffer buf;
  buf.height = h;
  buf.width = w;
  buf.data = rgb;
  return buf;
}
