#include <stdio.h>
#include <stdlib.h>
#include "Utils.h"
#include "Polygonate.h"
#include "Vector.h"

int main() {
  int32_t y[] = {1, 1, 2, 2, 2, 3, 3, 4, 4, 4, 5};
  int32_t x[] = {0, 4, 1, 2, 3, 2, 3, 1, 2, 4, 0};
  int32_t newSize = 0;
  float *lines = getPolygonOutline(x, y, 11, &newSize);
  for(int32_t i = 0; i < newSize; i += 2) {
    printLine(lines[i], lines[i + 1], lines[(i + 2) % newSize], lines[(i + 3) % newSize]);
  }
}