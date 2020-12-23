#pragma once
#include <stdint.h>

struct Vector_t {
  void *buffer;
  size_t capacity;
  size_t size;
  int8_t offsetSize;
};

typedef struct Vector_t *Vector;

Vector vct_Init(size_t size);
void vct_Push(Vector self, void *element);