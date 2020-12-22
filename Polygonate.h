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

typedef struct PlaneCoords_t *PlaneCoords;
struct PlaneCoords_t {
  int32_t *y;
  int32_t *x;
  size_t size;
};

Polygonate pg_Init(int32_t **map, int32_t h, int32_t w, int32_t island, int32_t freeSpace);
PlaneCoords pg_ComputeOutline(Polygonate self);
float *pg_CreatePolygon(Polygonate self);
void pg_ShowMap(Polygonate self);

