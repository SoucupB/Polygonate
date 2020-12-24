#include "../cmocka/cmk/cmocka.h"
#include <stdio.h>

static void null_test_success(void **state) {
  (void) state; /* unused */
  assert_true(1 == 1);
}

int main() {
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(null_test_success),
  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}