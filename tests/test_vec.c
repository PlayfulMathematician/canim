// test_vec.c example
#include <cmocka.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

#include "canim/math.h"

static void test_vec_zero(void **state) {
  (void)state;
  CanimVec2 v2 = {.x = 0, .y = 1};
  CanimVec2 u2 = {.x = 1, .y = 0};
  CanimVec2 sum2 = canim_add_vec(u2, v2);
  CanimVec3 v3 = {.x = 0, .y = 1, .z = 1};
  CanimVec3 u3 = {.x = 1, .y = 0, .z = 0};
  CanimVec3 sum3 = canim_add_vec(u3, v3);
  assert_float_equal(sum2.x, 1.0f, 1e-6);
  assert_float_equal(sum2.y, 1.0f, 1e-6);
  assert_float_equal(sum3.x, 1.0f, 1e-6);
  assert_float_equal(sum3.y, 1.0f, 1e-6);
  assert_float_equal(sum3.z, 1.0f, 1e-6);
}

int main(void) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_vec_zero),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
