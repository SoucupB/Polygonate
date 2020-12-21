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
  FILE *fd = fopen("result.txt", "w+");
  ut_ColoringMap(fd, n, m);
  for(int32_t i = 0; i < coords->size; i++) {
    map[coords->y[i]][coords->x[i]] = 2;
    printf("%d %d\n", coords->y[i], coords->x[i]);
  }

  for(int32_t i = 0; i < n; i++) {
    for(int32_t j = 0; j < m; j++) {
      if(map[i][j] == 2) {
        ut_ColoringCells(fd, i, j, 2);
        ut_ColoringCells(fd, i, j, 1);
      }
      else if(map[i][j] == 1) {
        ut_ColoringCells(fd, i, j, 1);
      }
    }
  }

  ut_ShowMap(map, n, m);


  fclose(fd);
}