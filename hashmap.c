#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}

void insertMap(HashMap * map, char * key, void * value) {
  int loc = hash(key, map->capacity);
  if(map->buckets[loc] == NULL)
  {
    map->buckets[loc] = createPair(key, value);
    map->buckets[loc]->value = value;
    map->buckets[loc]->key = key;
    map->size += 1; 
  }
  else if(is_equal(map->buckets[loc]->key, key))
  {
    map->buckets[loc]->value = value;
  }
  else if(map->buckets[loc] != NULL)
  {
    for(int i = loc; i < map->capacity; i++)
    {
      if(map->buckets[i] == NULL)
      {
        map->buckets[i] = createPair(key, value);
        map->buckets[i]->value = value;
        map->buckets[i]->key = key;
        map->size += 1;
      }
      else if(is_equal(map->buckets[i]->key, key))
      {
        map->buckets[i]->value = value;
      }
    }
    for(int i = 0; i < loc; i++)
    {
      if(map->buckets[i] == NULL)
      {
        map->buckets[i] = createPair(key, value);
        map->buckets[i]->value = value;
        map->buckets[i]->key = key;
        map->size += 1;
      }
      else if(is_equal(map->buckets[i]->key, key))
      {
        map->buckets[i]->value = value;
      }
    }
  }
}

void enlarge(HashMap * map) {
  enlarge_called = 1; //no borrar (testing purposes)
  int old_capacity = map->capacity;
  Pair** old_array = map->buckets;
  map->capacity = 2 * old_capacity;
  map->buckets = (Pair**)calloc(map->capacity, sizeof(Pair*));
  map->size = 0;

  for (int i = 0; i < old_capacity; i++)
  {
    if (old_array[i] != NULL)
    {
      insertMap(map, old_array[i]->key, old_array[i]->value);
      free(old_array[i]);
    }
  }
  free(old_array);
}


HashMap * createMap(long capacity) {
  HashMap* mapa = (HashMap*) malloc(sizeof(HashMap));
  mapa->capacity = capacity;
  mapa->buckets = (Pair**) malloc(capacity * sizeof(Pair*));
  for(int i = 0; i < capacity; i++)
  {
    mapa->buckets[i] = NULL;
  }
  mapa->current = -1;
  mapa->size = 0;
  return mapa;
}

void eraseMap(HashMap * map,  char * key) {    
  Pair* datoABorrar = searchMap(map, key);
  if(datoABorrar != NULL)
  {
    map->size -= 1;
    datoABorrar->key = NULL;
  }
}

Pair * searchMap(HashMap * map,  char * key) {   
  int loc = hash(key, map->capacity);
  while(map->buckets[loc] != NULL && map->buckets[loc]->key != NULL)
  {
    map->current = loc;
    if(is_equal(map->buckets[loc]->key, key))
    {
      return map->buckets[loc];
    }
    loc = (loc + 1) % map->capacity;
  }
  return NULL;
}

Pair * firstMap(HashMap * map) {
  for(int i = 0; i < map->capacity; i++)
  {
    if(map->buckets[i]->key != NULL && map->buckets[i] != NULL)
    {
      map->current = i;
      return map->buckets[i];
    }
  }
  return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
