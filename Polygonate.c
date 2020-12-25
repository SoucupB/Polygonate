#include "Polygonate.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

PlaneCoords computeOutline(Polygonate self, int32_t stY, int32_t stX);

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

float *getPolygonOutline(int32_t *xS, int32_t *yS, int32_t size, int32_t *newSize) {
  int32_t minX = INF;
  int32_t minY = INF;
  int32_t maxX = 0;
  int32_t maxY = 0;
  for(int32_t i = 0; i < size; i++) {
    if(xS[i] < minX) {
      minX = xS[i];
    }
    if(xS[i] > maxX) {
      maxX = xS[i];
    }
  }
  for(int32_t i = 0; i < size; i++) {
    if(yS[i] < minY) {
      minY = yS[i];
    }
    if(yS[i] > maxY) {
      maxY = yS[i];
    }
  }
  int32_t w = maxX - minX + 3;
  int32_t h = maxY - minY + 3;
  int32_t **buffer = malloc(sizeof(int32_t *) * h);
  for(int32_t i = 0; i < h; i++) {
    buffer[i] = malloc(sizeof(int32_t) * w);
    memset(buffer[i], 0, sizeof(int32_t) * w);
  }
  for(int32_t i = 0; i < size; i++) {
    buffer[yS[i] - minY + 1][xS[i] - minX + 1] = 1;
  }
  Polygonate poly = pg_Init(buffer, h, w, 1, 0);
  pg_ShowMap(poly);
  Vector result = pg_CreatePolygon(poly);
  *newSize = result->size;
  float *linesBuffer = result->buffer;
  for(int32_t i = 0; i < *newSize; i += 2) {
    linesBuffer[i] += minX;
    linesBuffer[i + 1] += minY;
  }
  free(result);
  return linesBuffer;
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

PlaneCoords pg_ComputeOutlineFromPoint(Polygonate self, float stY, float stX) {
  return computeOutline(self, stY, stX);
}

PlaneCoords computeOutline(Polygonate self, int32_t stY, int32_t stX) {
  PlaneCoords coords = malloc(sizeof(struct PlaneCoords_t));
  coords->x = vct_Init(sizeof(int32_t));
  coords->y = vct_Init(sizeof(int32_t));
  int32_t endX = -1;
  int32_t endY = -1;
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
        vct_Push(coords->x, &dEndX);
        vct_Push(coords->y, &dEndY);
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

PlaneCoords pg_ComputeOutline(Polygonate self) {
  int32_t stY;
  int32_t stX;
  getStartPixel(self, &stY, &stX);
  return computeOutline(self, stY, stX);
}

void pg_ShowMap(Polygonate self) {
  for(int32_t i = 0; i < self->h; i++) {
    for(int32_t j = 0; j < self->w; j++) {
      printf("%d", self->map[i][j]);
    }
    printf("\n");
  }
}

void pg_Delete(Polygonate self) {
  for(int32_t i = 0; i < self->h; i++) {
    free(self->map[i]);
  }
  free(self->map);
  free(self);
}

void pg_SoftDelete(Polygonate self) {
  free(self);
}

void deleteBuffer(float *buffer) {
  free(buffer - 1);
}

Vector removeDoublePoints(Vector src) {
  Vector dst = vct_Init(sizeof(float));
  for(int32_t i = 0; i < src->size; i += 2) {
    int8_t checker = 1;
    for(int32_t j = 0; j < src->size; j += 2) {
      if(i != j && ((float *)src->buffer)[i] == ((float *)src->buffer)[j] && ((float *)src->buffer)[i + 1] == ((float *)src->buffer)[j + 1]) {
        checker = 0;
        break;
      }
    }
    if(checker) {
      float x = ((float *)src->buffer)[i];
      float y = ((float *)src->buffer)[i + 1];
      vct_Push(dst, &x);
      vct_Push(dst, &y);
    }
  }
  vct_Delete(src);
  return dst;
}

// void pg_ShowLines(Vector lines) {
//   printf("%d\n", (int32_t)lines->size);
//   float *allLines = (float *)lines->buffer;
//   for(int32_t i = 0; i < (int32_t)lines->size; i += 2) {
//     printf("(%f, %f)\n", allLines[i], allLines[i + 1]);
//   }
//   printf("\n");
//   for(int32_t i = 0; i < (int32_t)lines->size; i += 2) {
//     printLine(allLines[i], allLines[i + 1], allLines[(i + 2) % lines->size], allLines[(i + 3) % lines->size]);
//   }
// }

Vector pg_CreatePolygon(Polygonate self) {
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
  Vector lines = vct_Init(sizeof(float));
  for(int32_t i = 0; i < coords->x->size; i++) {
    while(i < coords->x->size - 1 && (float)((((int32_t *)coords->x->buffer)[i] >> 1) + (((int32_t *)coords->x->buffer)[i] & 1)) ==
                                     (float)((((int32_t *)coords->x->buffer)[i + 1] >> 1) + (((int32_t *)coords->x->buffer)[i + 1] & 1))
                                  && (float)((((int32_t *)coords->y->buffer)[i] >> 1) + (((int32_t *)coords->y->buffer)[i] & 1)) ==
                                     (float)((((int32_t *)coords->y->buffer)[i + 1] >> 1) + (((int32_t *)coords->y->buffer)[i + 1] & 1))) {
      i++;
    }
    int32_t x = ((int32_t *)coords->x->buffer)[i];
    int32_t y = ((int32_t *)coords->y->buffer)[i];
    float valX = (float)((x >> 1) + (x & 1));
    float valY = (float)((y >> 1) + (y & 1));
    vct_Push(lines, &valX);
    vct_Push(lines, &valY);
  }
  pg_Delete(expand);
  return removeDoublePoints(lines);
}