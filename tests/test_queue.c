#include <stdio.h>
#include <assert.h>
#include "queue.h"

int main() {
    printf("=== Start Testing Queue ===\n");

    ds_queue q;
    ds_queue_init(&q);

    // 1. 初始状态
    assert(ds_queue_empty(&q) == true);
    assert(ds_queue_size(&q) == 0);
    printf("[PASS] Init\n");

    int data[] = {1, 2, 3};

    // 2. 入队 (Push) - 模拟排队
    // 队伍: [1]
    printf("Push 1\n");
    ds_queue_push(&q, &data[0]);
    assert(*(int*)ds_queue_front(&q) == 1);
    assert(*(int*)ds_queue_back(&q)  == 1);

    // 队伍: [1, 2]
    printf("Push 2\n");
    ds_queue_push(&q, &data[1]);
    assert(*(int*)ds_queue_front(&q) == 1); // 头还是 1
    assert(*(int*)ds_queue_back(&q)  == 2); // 尾变成 2

    // 队伍: [1, 2, 3]
    printf("Push 3\n");
    ds_queue_push(&q, &data[2]);
    assert(*(int*)ds_queue_front(&q) == 1); // 头还是 1
    assert(*(int*)ds_queue_back(&q)  == 3); // 尾变成 3
    
    assert(ds_queue_size(&q) == 3);
    printf("[PASS] Push (FIFO Logic)\n");

    // 3. 出队 (Pop) - 必须是 1 先出来
    
    // Pop 1
    ds_queue_pop(&q);
    // 现在队伍应该是 [2, 3]
    assert(ds_queue_size(&q) == 2);
    assert(*(int*)ds_queue_front(&q) == 2); // 新的头应该是 2
    printf("Popped 1, new front is 2\n");

    // Pop 2
    ds_queue_pop(&q);
    // 现在队伍应该是 [3]
    assert(*(int*)ds_queue_front(&q) == 3);
    printf("Popped 2, new front is 3\n");

    // Pop 3
    ds_queue_pop(&q);
    assert(ds_queue_empty(&q) == true);
    printf("Popped 3, queue is empty\n");

    printf("[PASS] Pop\n");

    // 4. 释放
    ds_queue_free(&q);
    printf("[PASS] Free\n");

    printf("\n*** ALL QUEUE TESTS PASSED ***\n");
    return 0;
}