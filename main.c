#include <stdio.h>
#include <stdlib.h>
#include "Polygonate.h"
#include "Utils.h"

int main() {
  int32_t n, m;
  int32_t **map = readFile(&n, &m);
  ut_ShowMap(map, n, m);
  Polygonate poly = pg_Init(map, n, m, 1, 0);
  PlaneCoords coords = pg_ComputeOutline(poly);
  for(int32_t i = 0; i < coords->size; i++) {
    map[coords->y[i]][coords->x[i]] = 2;
    printf("%d %d\n", coords->y[i], coords->x[i]);
  }
  ut_ShowMap(map, n, m);
}