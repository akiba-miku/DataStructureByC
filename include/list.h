#ifndef DS_LIST_H
#define DS_LIST_H

#include <stddef.h>

typedef struct ds_node{
    void *data;
    struct ds_node *prev;
    struct ds_node *next;
}ds_node;

typedef struct{
    ds_node *head;
    ds_node *tail;
    size_t size;
}ds_list;


void ds_list_init(ds_list *list);

void ds_list_free(ds_list *list);

//insert and delete
void ds_list_push_back(ds_list *list, void *item);
void ds_list_push_front(ds_list *list, void *item);
void ds_list_remove_at_i(ds_list *list, size_t index);

void *ds_list_back(ds_list *list);
void *ds_list_front(ds_list *list);


#endif