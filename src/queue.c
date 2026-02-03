#include "queue.h"
#include <stddef.h> // for NULL

// init
void ds_queue_init(ds_queue *queue){
    ds_list_init(&queue->list);
}

// destroy
void ds_queue_free(ds_queue *queue){
    ds_list_free(&queue->list);
}

// (Standard: Push Back)
void ds_queue_push(ds_queue *queue, void *item){
    ds_list_push_back(&queue->list, item);
}

// (Standard: Pop Front / Remove Index 0)
void ds_queue_pop(ds_queue *queue){
    if(!ds_queue_empty(queue)) {
        ds_list_remove_at_i(&queue->list, 0);
    }
}

// (Front)
void *ds_queue_front(ds_queue *queue){
    if(ds_queue_empty(queue)){
        return NULL;
    }
    return ds_list_front(&queue->list);
}

// (Back)
void *ds_queue_back(ds_queue *queue){
    if(ds_queue_empty(queue)){
        return NULL;
    }
    return ds_list_back(&queue->list);
}

// is_empty
bool ds_queue_empty(ds_queue *queue){
    return queue->list.size == 0;
}

// get_size
size_t ds_queue_size(ds_queue *queue){
    return queue->list.size;
}