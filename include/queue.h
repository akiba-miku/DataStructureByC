#ifndef DS_QUEUE_H
#define DS_QUEUE_H

#include <stdbool.h>
#include "list.h" // 这一次，我们要复用链表！

typedef struct {
    ds_list list; // 组合模式：队列里包着一个链表
} ds_queue;

// 初始化
void ds_queue_init(ds_queue *q);

// 销毁
void ds_queue_free(ds_queue *q);

// 入队 (Enqueue) - 尾部进
void ds_queue_push(ds_queue *q, void *data);

// 出队 (Dequeue) - 头部出
void ds_queue_pop(ds_queue *q);

// 获取队头元素 (Front)
void *ds_queue_front(ds_queue *q);

// 获取队尾元素 (Back) - 虽然队列通常只看头，但有这个接口也很方便
void *ds_queue_back(ds_queue *q);

// 判空
bool ds_queue_empty(ds_queue *q);

// 大小
size_t ds_queue_size(ds_queue *q);

#endif