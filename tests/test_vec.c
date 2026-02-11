// test_vec.c example
#include <cmocka.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

#include "canim/math.h"

static void test_vec_zero(void **state) {
  (void)state;
  CanimVec2 v = {.x = 0, .y = 1};
  CanimVec2 u = {.x = 1, .y = 0};
  CanimVec2 sum = canim_add_vec2(u, v);
  assert_float_equal(sum.x, 1.0f, 1e-6);
  assert_float_equal(sum.y, 1.0f, 1e-6);
}

int main(void) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_vec_zero),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
