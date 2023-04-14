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



void insertMap(HashMap * map, char * key, void * value){
    if(map == NULL || key == NULL) return;
    
    if(searchMap(map, key) != NULL) return;
    
    long pos = hash(key, map->capacity);

    while(map->buckets[pos] != NULL && map->buckets[pos]->key != NULL){
        pos = (pos + 1) % map->capacity;
    }
    
    Pair * new_pair = createPair(key, value);
    map->buckets[pos] = new_pair;
    
    map->size++;
    map->current = pos;
    
    if(map->size >= map->capacity/2){
        enlarge(map);
    }
}

void enlarge(HashMap * map) {
  enlarge_called = 1; //no borrar (testing purposes)
  Pair ** old_buckets = map->buckets;
  long old_capacity = map->capacity;
  map->capacity *= 2;
  map->buckets = (Pair **)malloc(sizeof(Pair *) * map->capacity);
  map->size = 0;
  for (int i = 0; i < old_capacity; i++) {
    Pair * pair = old_buckets[i];
    if (pair != NULL && pair->key != NULL) {
        insertMap(map, pair->key, pair->value);
    }
  }  
}

  
  


HashMap * createMap(long capacity) {
    HashMap *map = (HashMap *) malloc(sizeof(HashMap));
    if (map == NULL) {
        return NULL;
    }
    map->buckets = (Pair **) calloc(capacity, sizeof(Pair *));
    if (map->buckets == NULL) {
        free(map);
        return NULL;
    }
    map->size = 0;
    map->capacity = capacity;
    map->current = -1;
    return map;
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
