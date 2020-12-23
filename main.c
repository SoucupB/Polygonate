#include <stdio.h>
#include <stdlib.h>
#include "Polygonate.h"
#include "Utils.h"
#include "Vector.h"

int main() {
  int32_t n, m;
  int32_t **map = readFile(&n, &m);
  Polygonate poly = pg_Init(map, n, m, 1, 0);
  Vector lines = pg_CreatePolygon(poly);
  FILE *fr = fopen("lines.txt", "w+");
  printf("%d\n", (int32_t)lines->size);
  for(int32_t i = 0; i < (int32_t)lines->size; i += 2) {
    printf("(%f, %f)\n", ((float *)lines->buffer)[i], ((float *)lines->buffer)[i + 1]);
    fprintLine(fr, ((float *)lines->buffer)[i], ((float *)lines->buffer)[i + 1], ((float *)lines->buffer)[(i + 2) % lines->size], ((float *)lines->buffer)[(i + 3) % lines->size]);
  }
  pg_ShowMap(poly);
  PlaneCoords coords = pg_ComputeOutline(poly);
  FILE *fd = fopen("result.txt", "w+");
  ut_ColoringMap(fd, n, m);
  for(int32_t i = 0; i < coords->x->size; i++) {
    map[((int32_t *)coords->y->buffer)[i]][((int32_t *)coords->x->buffer)[i]] = 2;
    printf("%d %d\n", ((int32_t *)coords->y->buffer)[i], ((int32_t *)coords->x->buffer)[i]);
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
  pg_ShowMap(poly);
  fclose(fd);
}