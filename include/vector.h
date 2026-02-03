#ifndef DS_VECTOR_H
#define DS_VECTOR_H
#include<stddef.h>
typedef struct{
    void** data;
    size_t size;
    size_t capacity;
}ds_vector;

void ds_vector_init(ds_vector* v, size_t initial_capacity);

void ds_vector_add(ds_vector* v, void* item);
void ds_vector_remove_at_i(ds_vector *v, size_t index);
void *ds_vector_get(ds_vector* v, size_t index);
void ds_vector_set(ds_vector* v,size_t index, void* item);

void ds_vector_free(ds_vector* v);

#endif