// SPDX-License-Identifier: GPL-3.0
#include "canim/data.h"
#include "canim/log.h"
#include "canim/math.h"
#include <cmocka.h>
#include <stdarg.h>
#include <stddef.h>

static void test_vec_zero(void **state) {
  (void)state;

  CANIM_CREATE_LOGGER(CANIM_LOG_LEVEL_INFO);
  CanimDA da_int = CANIM_DA_INIT(int);
  CANIM_DA_PUSH(&da_int, 10);
  CANIM_DA_PUSH(&da_int, 20);
  assert_int_equal(CANIM_DA_GET(da_int, int, 0), 10);
  assert_int_equal(CANIM_DA_GET(da_int, int, 1), 20);
  int *last;
  CANIM_DA_POP(da_int, last);
  assert_int_equal(*last, 20);
  CANIM_DA_PUSH(&da_int, 10);

  assert_int_equal(CANIM_DA_GET(da_int, int, 1), 10);
  CanimDA da_vec3 = CANIM_DA_INIT(CanimVec3);
  CanimVec3 vc03 = (CanimVec3){.x = 0, .y = 0, .z = 0};
  CANIM_DA_PUSH(&da_vec3, vc03);
  CanimVec3 vc13 = (CanimVec3){.x = 1, .y = 0, .z = 0};
  CANIM_DA_PUSH(&da_vec3, vc13);
  assert_float_equal(CANIM_DA_GET(da_vec3, CanimVec3, 0).x, 0, 1e-6);
  assert_float_equal(CANIM_DA_GET(da_vec3, CanimVec3, 0).y, 0, 1e-6);
  assert_float_equal(CANIM_DA_GET(da_vec3, CanimVec3, 0).z, 0, 1e-6);
  assert_float_equal(CANIM_DA_GET(da_vec3, CanimVec3, 1).x, 1, 1e-6);
  assert_float_equal(CANIM_DA_GET(da_vec3, CanimVec3, 1).y, 0, 1e-6);
  assert_float_equal(CANIM_DA_GET(da_vec3, CanimVec3, 1).z, 0, 1e-6);
}

int main(void) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_vec_zero),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
