#include"stack.h"
#define DEFAULT_STACK_SIZE 4

void ds_stack_init(ds_stack *stack){
    ds_vector_init(&stack->vec, DEFAULT_STACK_SIZE);
}

void ds_stack_free(ds_stack *stack){
    ds_vector_free(&stack->vec);
}

void ds_stack_push(ds_stack *stack, void *data){
    ds_vector_add(&stack->vec, data);
}

void ds_stack_pop(ds_stack *stack){
    if(!ds_stack_empty(stack))
        ds_vector_remove_at_i(&stack->vec, stack->vec.size-1);
}

void *ds_stack_top(ds_stack *stack){
    if(ds_stack_empty(stack)) return NULL;
    return ds_vector_get(&stack->vec, stack->vec.size-1);
}

bool ds_stack_empty(ds_stack *stack){
    return stack->vec.size == 0;
}

size_t ds_stack_size(ds_stack *stack){
    return stack->vec.size;
}