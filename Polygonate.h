#include <stdint.h>
#pragma once

typedef struct Polygonate_t *Polygonate;
struct Polygonate_t {
  int32_t **map;
  int32_t w;
  int32_t h;
  int32_t island;
  int32_t freeSpace;
};

Polygonate pg_Init(int32_t **map, int32_t h, int32_t w, int32_t island, int32_t freeSpace);

