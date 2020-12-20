#pragma once
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
void ut_ShowMap(int32_t **map, int32_t h, int32_t w) {
  for(int32_t i = 0; i < h; i++) {
    for(int32_t j = 0; j < w; j++) {
      printf("%d", map[i][j]);
    }
    printf("\n");
  }
}

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