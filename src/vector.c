#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"vector.h"
#define DEFAULT_CAPACITY 16
#define DEFAULT_EXPANSION_FACTOR 1.5


//initial the dynamic array

void ds_vector_init(ds_vector *v, size_t inital_capacity){
    if(inital_capacity == 0){
        inital_capacity = DEFAULT_CAPACITY;
    }

    v->capacity = inital_capacity;
    v->size = 0;
    v->data = malloc(sizeof(void *) * inital_capacity);

    if(v->data == NULL){
        perror("initalize ds_vector failed!");
        exit(1);
    }
}

//add at the last pos.
void ds_vector_add(ds_vector *v, void* item){
    //Consider the Resize situation
    if(v->capacity == v->size){
        size_t new_capacity = (size_t)(DEFAULT_EXPANSION_FACTOR * v->capacity);
        if(new_capacity == v->capacity) new_capacity++;

        void **new_v = realloc(v->data, sizeof(void *) * new_capacity);

        if(new_v == NULL){
            perror("ds_vector: resize failed");
            exit(1);
        }

        v->data = new_v;
        v->capacity = new_capacity;
    }
    v->data[v->size++] = item;
}

void ds_vector_remove_at_i(ds_vector *v, size_t index){
    if(index >= v->size){
        return ;
    }
    if(index < v->size - 1){
        void **dest = v->data + index;
        void **src = dest + 1;

        size_t items_to_remove = v->size - index - 1;
        memmove(dest, src, sizeof(void *) * (items_to_remove));
    }
    v->size--;
    v->data[v->size] = NULL;
}

//get at index
void *ds_vector_get(ds_vector *v, size_t index){
    if(index >= v->size){
        return NULL;
    }
    return v->data[index];
}

//set value at index
void ds_vector_set(ds_vector *v, size_t index, void *item){
    if(index >= v->size){
        return ;
    }
    v->data[index] = item;
}

//destroy all items if they are in heap 
void ds_vector_free(ds_vector *v){
    for(size_t i=0;i<v->size;i++){
        free(v->data[i]);
    }
}

