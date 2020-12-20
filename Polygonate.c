#include "Polygonate.h"
#include <stdlib.h>

Polygonate pg_Init(int32_t **map, int32_t h, int32_t w, int32_t island, int32_t freeSpace) {
  Polygonate self = malloc(sizeof(struct Polygonate_t));
  self->map = map;
  self->h = h;
  self->w = w;
  self->island = island;
  self->freeSpace = freeSpace;
  return self;
}

void pg_GetStartPixel(Polygonate self, int32_t *y, int32_t *x) {
  for(int32_t i = 0; i < self->h; i++) {
    for(int32_t j = 0; j < self->w; j++) {
      if(self->map[i][j] == self->island) {
        *y = i;
        *x = j;
        return ;
      }
    }
  }
  *y = -1;
  *x = -1;
}