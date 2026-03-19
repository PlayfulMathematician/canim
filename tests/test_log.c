#define CANIM_DEBUG
#include <canim/log.h>
#include <stdio.h>
int main() {
  CANIM_CREATE_LOGGER(CANIM_LOG_LEVEL_INFO);
  CANIM_LOG(CANIM_LOG_LEVEL_WARNING, "Hi %s", "John");
  CANIM_LOG(CANIM_LOG_LEVEL_INFO, "Hi");
}
