#ifndef DS_HASHMAP_H
#define DS_HASHMAP_H

#include<stdbool.h>
#include<stddef.h>
#include"list.h"

typedef struct{
    char *key;
    void *value;
}ds_entry;

typedef struct{
    ds_list *buckets;
    size_t size;
    size_t capacity;
    float factor;
}ds_hashmap;

void ds_hashmap_init(ds_hashmap *hashmap, size_t inital_capacity);
void ds_hashmap_free(ds_hashmap *hashmap);

void ds_hashmap_put(ds_hashmap *hashmap, const char *key, void *value);
void *ds_hashmap_get(ds_hashmap *hashmap, const char *key);
void ds_hashmap_remove(ds_hashmap *hashmap, const char *key);

bool ds_hashmap_empty(ds_hashmap *hashmap);
size_t ds_hashmap_size(ds_hashmap *hashmap);

#endif