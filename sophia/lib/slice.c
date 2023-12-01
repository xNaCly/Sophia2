#include "slice.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SLICE_MIN_SIZE 8

Slice *sliceNew(size_t initial_size) {
  Slice *s = NULL;
  if (s = malloc(sizeof(Slice)), s == NULL) {
    fprintf(stderr, "sealib: failed to allocate a slice");
    exit(EXIT_FAILURE);
  }
  s->elements = NULL;
  initial_size = initial_size < SLICE_MIN_SIZE ? SLICE_MIN_SIZE : initial_size;
  if (s->elements = malloc(initial_size * sizeof(void *)),
      s->elements == NULL) {
    fprintf(stderr,
            "sealib: failed to allocate the underlying array of size %zu\n",
            initial_size);
    exit(EXIT_FAILURE);
  }
  s->cap = initial_size;
  s->len = 0;
  return s;
}

// duplicates the cap of the slice and the allocated space of the underlying
// array
static void grow_slice(Slice *s) {
  void **t = NULL;
  if (t = malloc(s->cap * 2 * sizeof(void *)), t == NULL) {
    fprintf(stderr,
            "sealib: failed to grow the slice from %zu to %zu (allocation "
            "failed)\n",
            s->cap, s->cap * 2);
    exit(EXIT_FAILURE);
  }
  for (size_t i = 0; i < s->len; i++) {
    t[i] = s->elements[i];
  }
  free(s->elements);
  s->elements = t;
  s->cap *= 2;
}

void sliceAppend(Slice *s, void *element) {
  // if we append and the new len is bigger or equal to the size we double the
  // slice, therefore we make a good tradeoff between times we need to grow
  // the slice and the amount of memory we take up
  if (s->len + 1 > s->cap) {
    grow_slice(s);
  }

  s->elements[s->len] = element;
  s->len++;
}

void *sliceGet(Slice *s, int index) {
  if (index < 0) {
    return NULL;
  }
  size_t i = (size_t)index;
  if (i >= s->cap || i >= s->len) {
    return NULL;
  }
  return s->elements[i];
}

void **sliceGetArray(Slice *s) { return s->elements; }

void sliceFree(Slice *s) {
  free(s->elements);
  free(s);
  s = NULL;
}
