#include<stdlib.h>
#include<string.h>
#include"hashmap.h"
#define DEFALUT_HASHMAP_CAPACITY 16
#define DEFAULT_HASHMAP_FACTOR 0.75
#define DEFAULT_HASHMAP_EXPAND_FACTOR 1.5
//deeply copy string
static char *my_strdup(const char *s) {
    size_t len = strlen(s) + 1;
    char *new_s = malloc(len);
    if (new_s) memcpy(new_s, s, len);
    return new_s;
}

// dib2 algorithm
static size_t hash_function(const char *key){
    size_t hash = 5381;
    size_t c;
    while((c = *key++) != 0){
        hash = (hash << 5) + hash + c; // be equal to (hash * 33 + c)
    }
    return hash;
}

void ds_hashmap_init(ds_hashmap *hashmap, size_t inital_capacity){
    if(inital_capacity == 0){
        inital_capacity = DEFALUT_HASHMAP_CAPACITY;
    }
    hashmap->buckets = (ds_list *)malloc(sizeof(ds_list) * inital_capacity);
    hashmap->size = 0;
    hashmap->capacity = inital_capacity;
    hashmap->factor = DEFAULT_HASHMAP_FACTOR;
    for(size_t i=0;i<inital_capacity;i++){
        ds_list_init(hashmap->buckets + i);
    }
}

void ds_hashmap_free(ds_hashmap *hashmap){
    for(size_t i=0;i<hashmap->capacity;i++){
        ds_list *bucket = hashmap->buckets + i;
        ds_node *cur = bucket->head;
        while(cur != NULL){
            ds_entry *entry = cur->data;
            free(entry->key);
            free(entry);
            cur = cur->next;
        }
        ds_list_free(bucket);
    }
    free(hashmap->buckets);
    hashmap->buckets = NULL;
    hashmap->size = hashmap->capacity = 0;
}


//resize function
void resize(ds_hashmap *hashmap){
    size_t new_capacity = (size_t)hashmap->capacity * DEFAULT_HASHMAP_EXPAND_FACTOR;
    if(new_capacity == hashmap->size) new_capacity++;
    
    ds_list *new_buckets = (ds_list *)malloc(sizeof(ds_list) * new_capacity);
    for(size_t i=0;i<new_capacity;i++) ds_list_init(new_buckets+i);

    for(size_t i=0;i<hashmap->capacity;i++){
        ds_list *bucket = hashmap->buckets+i;
        ds_node *cur = bucket->head;
        while(cur != NULL){
            ds_entry *entry = cur->data;

            const char *key = (const char *)entry->key;
            size_t hash = hash_function(key);
            size_t index = hash % new_capacity;

            ds_list_push_back(&new_buckets[index], entry);

            cur = cur->next;
        }
        ds_list_free(bucket);
    }
    free(hashmap->buckets);
    hashmap->buckets = new_buckets;
    hashmap->capacity = new_capacity;
}
void ds_hashmap_put(ds_hashmap *hashmap, const char *key, void *value){
    if(hashmap->size >= hashmap->capacity * hashmap->factor){
        resize(hashmap);
    }
    size_t hash = hash_function(key);
    size_t index = hash % hashmap->capacity;

    ds_list *bucket = &hashmap->buckets[index];
    ds_node *cur = bucket->head;
    while(cur != NULL){
        ds_entry *entry = cur->data;
        if(strcmp(entry->key, key) == 0){
            entry->value = value;
            return ;
        }
        cur = cur->next;
    }
    ds_entry *new_entry = (ds_entry *)malloc(sizeof(ds_entry));
    new_entry->key = my_strdup(key);
    new_entry->value = value;
    ds_list_push_back(bucket, new_entry);
    hashmap->size++;
}


void *ds_hashmap_get(ds_hashmap *hashmap, const char *key){
    size_t hash = hash_function(key);
    size_t index = hash % hashmap->capacity;
    ds_list *bucket = &hashmap->buckets[index];
    ds_node *cur = bucket->head;
    while(cur != NULL){
        ds_entry *entry = cur->data;
        if(strcmp(entry->key, key) == 0){
            return entry->value;
        }
        cur = cur->next;
    }
    return NULL;
}

void ds_hashmap_remove(ds_hashmap *hashmap, const char *key){
    size_t hash = hash_function(key);
    size_t index = hash % hashmap->capacity;
    ds_list *bucket = &hashmap->buckets[index];
    ds_node *cur = bucket->head;
    for(size_t i=0;i<bucket->size;i++){
        ds_entry *entry = cur->data;
        if(strcmp(entry->key, key) == 0){
            free(entry->key);
            free(entry);
            ds_list_remove_at_i(bucket, i);
            hashmap->size--;
            break;
        }
        cur = cur->next;
    }
}
size_t ds_hashmap_size(ds_hashmap *hashmap) {
    return hashmap->size;
}

bool ds_hashmap_empty(ds_hashmap *hashmap) {
    return hashmap->size == 0;
}