#include <stdio.h>
#include <stdlib.h>
#include "Polygonate.h"
#include "Utils.h"

int main() {
  int32_t n, m;
  int32_t **map = readFile(&n, &m);
  ut_ShowMap(map, n, m);
}