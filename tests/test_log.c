// SPDX-License-Identifier: GPL-3.0
#include <canim/log.h>
int main() {
  CANIM_CREATE_LOGGER(CANIM_LOG_LEVEL_INFO);
  CANIM_LOG(CANIM_LOG_LEVEL_WARNING, "Hi %s", "John");
  CANIM_LOG(CANIM_LOG_LEVEL_INFO, "Hi");
}
