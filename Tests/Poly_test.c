#include "../cmocka/cmk/cmocka.h"
#include <stdio.h>
#include "../Polygonate.h"
#include <stdlib.h>

int32_t **copyMap(int32_t *src, int32_t h, int32_t w) {
  int32_t **dst = malloc(sizeof(int32_t *) * h);
  for(int32_t i = 0; i < h; i++) {
    dst[i] = malloc(sizeof(int32_t) * w);
    for(int32_t j = 0; j < w; j++) {
      dst[i][j] = src[i * h + j];
    }
  }
  return dst;
}

static void test_simple_polygon(void **state) {
  int32_t map[25]   = { 0, 0, 0, 1, 0,
                        0, 1, 1, 0, 0,
                        0, 1, 1, 0, 0,
                        0, 1, 1, 0, 0,
                        0, 0, 0, 0, 0 };
  const int32_t h = 5;
  const int32_t w = 5;
  int32_t **buffer = copyMap(map, h, w);
  Polygonate poly = pg_Init(buffer, h, w, 1, 0);
  Vector lines = pg_CreatePolygon(poly);
  pg_ShowLines(lines);
  assert_true(lines->size != 0);
}

int main() {
  const struct CMUnitTest tests[] = {
    cmocka_unit_test_prestate(test_simple_polygon, NULL),
  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}