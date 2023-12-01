#include "map.h"
#include "slice.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const unsigned int FNV_OFFSET_BASIS = 0x811c9dc5;
const unsigned int FNV_PRIME = 0x01000193;

// Computes a reproducible hash for the given key see map.h preamble for
// hashing algorithm details
static unsigned int hash_key(Map *m, const char *key) {
  unsigned int h = FNV_OFFSET_BASIS;
  while (*key) {
    h ^= *key++;
    h *= FNV_PRIME;
  }
  // This is a fast mod implementation, only works for powers of 2, see
  // https://en.wikipedia.org/wiki/Modulo#Performance_issues
  return h & (m->table_size - 1);
}

Map *mapNew() {
  Map *m = NULL;
  if (m = malloc(sizeof(Map)), m == NULL) {
    fprintf(stderr, "failed to malloc map");
    return NULL;
  }
  m->size = 0;
  m->table_size = INITIAL_SIZE;
  m->buckets = (Slice **)malloc(sizeof(Slice) * INITIAL_SIZE);
  for (int i = 0; i < INITIAL_SIZE; i++) {
    m->buckets[i] = sliceNew(8);
  }
  return m;
}

void mapPut(Map *m, const char *key, void *value) {
  unsigned int hash = hash_key(m, key);
  MapElement *e = NULL;
  if (e = malloc(sizeof(MapElement)), e == NULL) {
    fprintf(stderr, "failed to allocate map element");
    return;
  }
  e->hasValue = 1;
  e->value = value;
  e->key = key;
  sliceAppend(m->buckets[hash], e);
  m->size++;
}

void *mapGet(Map *m, const char *key) {
  unsigned int hash = hash_key(m, key);
  Slice *slice = m->buckets[hash];
  MapElement **arr = (MapElement **)sliceGetArray(slice);
  for (size_t i = 0; i < slice->len; i++) {
    MapElement *t = arr[i];
    if (t->hasValue && strcmp(t->key, key) == 0) {
      return t->value;
    }
  }
  return NULL;
}

bool mapContains(Map *m, const char *key) {
  unsigned int hash = hash_key(m, key);
  Slice *slice = m->buckets[hash];
  MapElement **arr = (MapElement **)sliceGetArray(slice);
  for (size_t i = 0; i < slice->len; i++) {
    MapElement *t = arr[i];
    if (t->hasValue && strcmp(t->key, key) == 0) {
      return true;
    }
  }
  return false;
}

void mapRemove(Map *m, const char *key) {
  unsigned int hash = hash_key(m, key);
  Slice *slice = m->buckets[hash];
  MapElement **arr = (MapElement **)sliceGetArray(slice);
  for (size_t i = 0; i < slice->len; i++) {
    MapElement *t = arr[i];
    if (t->hasValue && strcmp(t->key, key) == 0) {
      t->hasValue = 0;
      t->value = 0;
      t->key = 0;
    }
  }
  m->size--;
}

void mapFree(Map *m) {
  if (m == NULL) {
    return;
  }
  for (int i = 0; i < INITIAL_SIZE; i++) {
    sliceFree(m->buckets[i]);
  }
  free(m);
  m = NULL;
}
