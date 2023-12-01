#ifndef MAP_H
#define MAP_H

#include "slice.h"
#include <stdbool.h>
#define INITIAL_SIZE 1024

typedef struct MapElement {
  const char *key;
  void *value;
  char hasValue;
} MapElement;

typedef struct Map {
  // elements count
  int size;
  // possible space
  int table_size;
  // buckets
  Slice **buckets;
} Map;

// allocates a new map, with size of INITIAL_SIZE
Map *mapNew();

// copies value, insert copy for key into map, mind the load factor!
void mapPut(Map *map, const char *key, void *value);

// checks if an object with the given key is present in the map
bool mapContains(Map *m, const char *key);

// get a pointer to a value from the map by key
void *mapGet(Map *map, const char *key);

// remove an object with the given key from the map
void mapRemove(Map *map, const char *key);

// destroy the map, set point to NULL
void mapFree(Map *map);

#endif
