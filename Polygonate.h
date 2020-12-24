#pragma once
#include <stdint.h>
#include "Vector.h"

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
  Vector y;
  Vector x;
};

Polygonate pg_Init(int32_t **map, int32_t h, int32_t w, int32_t island, int32_t freeSpace);
PlaneCoords pg_ComputeOutlineFromPoint(Polygonate self, float stY, float stX);
PlaneCoords pg_ComputeOutline(Polygonate self);
Vector pg_CreatePolygon(Polygonate self);
void pg_ShowMap(Polygonate self);
void pg_SoftDelete(Polygonate self);
void pg_ShowLines(Vector lines);

