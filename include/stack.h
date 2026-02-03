#ifndef DS_STACK_H
#define DS_STACK_H

#include <stdbool.h> 
#include<stddef.h>
#include "vector.h"  

//Composition , by dynamic array
typedef struct {
    ds_vector vec; 
} ds_stack;

// init
void ds_stack_init(ds_stack *s);

// destroy
void ds_stack_free(ds_stack *s);

// Push
void ds_stack_push(ds_stack *s, void *data);

//  Pop - just delete data but no return 
void ds_stack_pop(ds_stack *s);

// Peek
void *ds_stack_top(ds_stack *s);

// is_empty.
bool ds_stack_empty(ds_stack *s);

// get_size
size_t ds_stack_size(ds_stack *s);

#endif