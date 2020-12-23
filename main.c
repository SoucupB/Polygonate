#include <stdio.h>
#include <stdlib.h>
#include "Polygonate.h"
#include "Utils.h"
#include "Vector.h"

int main() {
  Vector ana = vct_Init(sizeof(float));
  float a = 5.3;
  vct_Push(ana, &a);
  vct_Push(ana, &a);
  vct_Push(ana, &a);
  vct_Push(ana, &a);
  vct_Push(ana, &a);
  vct_Push(ana, &a);
  vct_Push(ana, &a);
  vct_Push(ana, &a);
  vct_Push(ana, &a);
  vct_Push(ana, &a);
  for(int32_t i = 0; i < ana->size; i++) {
    printf("%f ", ((float*)ana->buffer)[i]);
  }
  printf("\n%I64d", ana->capacity);
  exit(0);
  int32_t n, m;
  int32_t **map = readFile(&n, &m);
  Polygonate poly = pg_Init(map, n, m, 1, 0);
  float *lines = pg_CreatePolygon(poly);
  FILE *fr = fopen("lines.txt", "w+");
  printf("%d\n", (int32_t)lines[-1]);
  for(int32_t i = 0; i < (int32_t)lines[-1]; i += 2) {
    printf("(%f, %f)\n", lines[i], lines[i + 1]);
    fprintLine(fr, lines[i], lines[i + 1], lines[(i + 2) % (int32_t)((int32_t)lines[-1])], lines[(i + 3) % (int32_t)((int32_t)lines[-1])]);
  }
  pg_ShowMap(poly);
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
  pg_ShowMap(poly);
  fclose(fd);
}