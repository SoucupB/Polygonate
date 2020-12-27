#include <stdio.h>
#include <stdlib.h>
#include "Utils.h"
#include "Polygonate.h"
#include "Vector.h"
#include <math.h>

int main() {
  int32_t n;
  int32_t m;
  int32_t **map = readFile(&n, &m);
  int32_t y[512];
  int32_t x[512];
  int32_t size = 0;
  int32_t newSize = 0;
  for(int32_t i = 0; i < n; i++) {
    for(int32_t j = 0; j < m; j++) {
      if(map[i][j] == 1) {
        y[size] = i;
        x[size] = j;
        size++;
      }
    }
  }
  float *lines = getPolygonOutline(x, y, size, &newSize);
  for(int32_t i = 0; i < newSize; i += 2) {
    printLine(lines[i], lines[i + 1], lines[(i + 2) % newSize], lines[(i + 3) % newSize]);
  }
  float buffer[] = {2.0f, 4.0f, 0.0f, 0.0f, 4.0f, 2.0f};
  regulatePolygons(buffer, 6, 0.5);

  float a, b, c, radians;
  a = 10000, b = -0.00001;
  radians = 180.0f / (1.0f / (atanf((a - b) / (1.0f + a * b)) / acos(-1.0f)));
  printf("%f %f %f %f", a, b, atanf((a - b) / (1.0f + a * b)), radians);
}