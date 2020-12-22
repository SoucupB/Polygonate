#include "Polygonate.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Polygonate pg_Init(int32_t **map, int32_t h, int32_t w, int32_t island, int32_t freeSpace) {
  Polygonate self = malloc(sizeof(struct Polygonate_t));
  self->map = map;
  self->h = h;
  self->w = w;
  self->island = island;
  self->freeSpace = freeSpace;
  return self;
}

void getStartPixel(Polygonate self, int32_t *y, int32_t *x) {
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

int8_t getRelativePosition(int32_t stX, int32_t stY, int32_t endX, int32_t endY) {
  int32_t dy[] = {-1, -1, -1, 0, 1, 1, 1, 0};
  int32_t dx[] = {-1, 0, 1, 1, 1, 0, -1, -1};
  int32_t deltaX = endX - stX;
  int32_t deltaY = endY - stY;
  for(int32_t i = 0; i < 8; i++) {
    if(deltaX == dx[i] && deltaY == dy[i]) {
      return i;
    }
  }
  return -1;
}

PlaneCoords pg_ComputeOutline(Polygonate self) {
  PlaneCoords coords = malloc(sizeof(struct PlaneCoords_t));
  coords->x = malloc(sizeof(int32_t) * self->h * self->w);
  coords->y = malloc(sizeof(int32_t) * self->h * self->w);
  coords->size = 0;
  int32_t stX;
  int32_t stY;
  int32_t endX = -1;
  int32_t endY = -1;
  getStartPixel(self, &stY, &stX);
  int32_t dy[] = {-1, -1, -1, 0, 1, 1, 1, 0};
  int32_t dx[] = {-1, 0, 1, 1, 1, 0, -1, -1};
  int32_t dEndX = stX;
  int32_t dEndY = stY;
  int32_t isDone = 0;
  int32_t i = 0;
  while(!isDone) {
    endX = dEndX;
    endY = dEndY;
    while(!isDone) {
      dEndX = endX;
      dEndY = endY;
      dEndX += dx[i];
      dEndY += dy[i];
      if(stX == dEndX && stY == dEndY) {
        isDone = 1;
      }
      if(dEndY >= 0 && dEndY < self->h && dEndX >= 0 && dEndX < self->w &&
         self->map[dEndY][dEndX] == self->island) {
        coords->x[coords->size] = dEndX;
        coords->y[coords->size] = dEndY;
        coords->size++;
        break;
      }
      else {
        i = (i + 1) % 8;
      }
    }
    if(i == 0) {
      i = 7;
    }
    else {
      i--;
    }
    i = getRelativePosition(dEndX, dEndY, endX + dx[i], endY + dy[i]);
  }
  return coords;
}

// void getLineFromPoint(int32_t pointPosition, int32_t nextPosition, float stY, float stX, float *y, float *x) {
//   if(pointPosition == 0 && nextPosition == 0) {
//     *y = stY + 1.0f;
//     *x = stX;
//   }
//   if(pointPosition == 2 && nextPosition == 0) {
//     *y = stY;
//     *x = stX;
//   }
//   if(pointPosition == 1 && nextPosition == 2) {
//     *y = stY + 1.0f;
//     *x = stX + 1.0f;
//   }
// }

void pg_ShowMap(Polygonate self) {
  for(int32_t i = 0; i < self->h; i++) {
    for(int32_t j = 0; j < self->w; j++) {
      printf("%d", self->map[i][j]);
    }
    printf("\n");
  }
}

float *pg_CreatePolygon(Polygonate self) {
  int32_t **expansionMap = malloc(sizeof(int32_t *) * self->h * 2);
  for(int32_t i = 0; i < self->h * 2; i++) {
    int32_t *row = malloc(sizeof(int32_t) * self->w * 2);
    for(int32_t j = 0; j < self->w * 2; j++) {
      row[j] = 0;
    }
    expansionMap[i] = row;
  }
  Polygonate expand = pg_Init(expansionMap, self->h * 2, self->w * 2, self->island, self->freeSpace);
  for(int32_t i = 0; i < self->h; i++) {
    for(int32_t j = 0; j < self->w; j++) {
      if(self->map[i][j] == self->island) {
        int32_t ii = i << 1;
        int32_t jj = j << 1;
        expand->map[ii][jj] = self->island;
        expand->map[ii][jj + 1] = self->island;
        expand->map[ii + 1][jj] = self->island;
        expand->map[ii + 1][jj + 1] = self->island;
      }
    }
  }
  PlaneCoords coords = pg_ComputeOutline(expand);
  for(int32_t i = 0; i < coords->size; i++) {
    printf("(%f, %f)\n", (float)(coords->x[i]), (float)(coords->y[i]));
  }
  printf("\n");
  pg_ShowMap(expand);
  return NULL;
}