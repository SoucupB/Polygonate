#include "Vector.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Vector vct_Init(size_t size) {
  Vector self = malloc(sizeof(struct Vector_t));
  self->size = 0;
  self->capacity = 1;
  self->offsetSize = size;
  self->buffer = malloc(size);
  return self;
}

void pushElement(Vector self, void *element) {
  memcpy(self->buffer + (self->size * self->offsetSize), element, self->offsetSize);
}

void vct_Push(Vector self, void *element) {
  if(self->capacity == self->size) {
    self->buffer = realloc(self->buffer, (self->capacity << 2) * self->offsetSize);
    self->capacity <<= 2;
  }
  pushElement(self, element);
  self->size++;
}

void vct_Delete(Vector self) {
  free(self->buffer);
  free(self);
}