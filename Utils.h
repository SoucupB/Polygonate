#pragma once
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int32_t **readFile(int *n, int *m) {
  FILE *fd = fopen("inputTests.txt", "r+");
  int8_t a = 0;
  fscanf(fd, "%d %d", n, m);
  fscanf(fd, "%c", &a);
  int32_t **map = malloc(sizeof(int32_t *) * *n);
  for(int32_t i = 0; i < *n; i++) {
    int32_t *row = malloc(sizeof(int32_t) * *m);
    for(int32_t j = 0; j < *m + 1; j++) {
      fscanf(fd, "%c", &a);
      if(a != '\n') {
        row[j] = a - 48;
      }
    }
    map[i] = row;
  }
  fclose(fd);
  return map;
}

void fprintLine(FILE *fd, float x, float y, float xx, float yy) {
  fprintf(fd, "(((1 - t) * %f + t * %f), ((1 - t) * %f + t * %f))\n", x, xx,
          y, yy);
}

void ut_ColoringCells(FILE *fd, int32_t y, int32_t x, int8_t type) {
  if(type == 1) {
    fprintLine(fd, x, y, x + 1.0, y + 1.0);
    //fprintLine(fd, x, y + 1.0, x + 1.0, y);
  }
  else {
    //fprintLine(fd, x, y + 0.5, x + 1.0, y + 0.5);
    //fprintLine(fd, x + 0.5, y, x + 0.5, y + 1.0);
    fprintLine(fd, x, y + 1.0, x + 1.0, y);
  }
}

void ut_ColoringMap(FILE *fd, int32_t n, int32_t m) {
  fprintLine(fd, 0, 0, 0, n);
  fprintLine(fd, 0, 0, m, 0);
  fprintLine(fd, 0, n, m, n);
  fprintLine(fd, m, 0, m, n);
  for(int32_t i = 0; i < n; i++) {
    fprintLine(fd, 0, i, m, i);
  }
  for(int32_t i = 0; i < m; i++) {
    fprintLine(fd, i, 0, i, n);
  }
}