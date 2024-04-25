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

int get_valid_location(HashMap* map, char* key)
{
  int start_loc = hash(key, map->capacity);
  if(map->buckets[start_loc]->key == key || map->buckets[start_loc] == NULL)
  {
    return start_loc;
  }
  else
  {
    int loc;
    for(loc = start_loc; loc < map->capacity; loc++)
    {
      if(map->buckets[loc] == NULL || map->buckets[loc]->key == key)
      {
        return loc;
      }
    }
    for(loc = 0; loc < start_loc; loc++)
    {
      if(map->buckets[loc] == NULL || map->buckets[loc]->key ==  || map->buckets[loc]->key == key)
        return loc;
    }
  }
  return -1;
}

void insertMap(HashMap * map, char * key, void * value) {
  int loc = get_valid_location(map, key);
  if(loc == -1)
  {
    enlarge(map);
    insertMap(map, key, value);
  }
  float load_factor = (float)map->size / map->capacity;
  if (load_factor > 0.7)
  {
    enlarge(map);
    insertMap(map, key, value);
  }
  else
  {
    map->buckets[loc]->value = value;
    map->buckets[loc]->key = key;
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


}

Pair * searchMap(HashMap * map,  char * key) {   


    return NULL;
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
