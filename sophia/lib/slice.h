#ifndef SLICE_H
#define SLICE_H

#include <stddef.h>

typedef struct Slice {
  // list of elements
  void **elements;
  // count of elements currenlty in list
  size_t len;
  // maxium size of Slice
  size_t cap;
} Slice;

// creates and returns a new slice, if initial_size is less than
// SLICE_MIN_SIZE, initial_size gets set to SLICE_MIN_SIZE.
Slice *sliceNew(size_t initial_size);

// inserts element at the given index, if s.len would be bigger than s.cap
// after insertion, doubles the size of the underlying array
void sliceAppend(Slice *s, void *element);

// returns the given element if 0 <= index < s.len
void *sliceGet(Slice *s, int index);

// returns pointer to the underlying array
void **sliceGetArray(Slice *s);

// frees the allocated memory region for the given Slice, sets the
// pointer to point to NULL
void sliceFree(Slice *s);

#endif
