#include<stdlib.h>
#include<stdio.h>
#include"list.h"

void ds_list_init(ds_list *list){
    list->head = list->tail = NULL;
    list->size = 0;
}

void ds_list_free(ds_list *list){
    ds_node *cur = list->head;
    while(cur!=NULL){
        ds_node *next = cur->next;
        free(cur);
        cur = next;
    }
    list->head = list->tail = NULL;
    list->size = 0;
}
void ds_list_push_back(ds_list *list, void *item){
    ds_node *node = (ds_node *)malloc(sizeof(ds_node));
    if(node == NULL){
        perror("Error: ds_list_push_back new_node creat failed!");
        exit(1);
    }
    node->data = item;
    if(list->head == NULL){
        list->head = list->tail = node;
        node->prev = NULL;
        node->next = NULL;
    }
    else{
        list->tail->next = node;
        node->prev = list->tail;
        node->next = NULL;
        list->tail = list->tail->next;
    }
    list->size++;
}

void ds_list_push_front(ds_list *list, void *item){
    ds_node *node = (ds_node *)malloc(sizeof(ds_node));
    if(node == NULL){
        perror("Error: ds_list_push_front new_node creat failed!");
        exit(1);
    }
    node->data = item;
    if(list->head == NULL){
        list->head = list->tail = node;
        node->prev = NULL;
        node->next = NULL;
    }
    else{
        node->next = list->head;
        list->head->prev = node;
        node->prev = NULL;
        list->head = list->head->prev;
    }
    list->size++;
}


//delete node at index
void ds_list_remove_at_i(ds_list *list, size_t index){
    if(index >= list->size){
        perror("Errpr: ds_list_remove Invaild Index");
        return ;    
    }
    ds_node *node = NULL;
    if(list->size == 1){
        node = list->head;
        list->head = list->tail = NULL;
    }
    else if(index == 0){
        node = list->head;
        list->head = list->head->next;
        list->head->prev = NULL;
    }
    else if(index == list->size-1){
        node = list->tail;
        list->tail = list->tail->prev;
        list->tail->next = NULL;
    }
    else{
        node = list->head;
        for(size_t i=0;i<index;i++){
            node = node->next;
        }
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    free(node);
    list->size--;
}

void *ds_list_front(ds_list *list){
    if(list->size == 0){
        return NULL;
    }
    return list->head->data;
}

void *ds_list_back(ds_list *list){
    if(list->size == 0){
        return NULL;
    }
    return list->tail->data;
}