#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

// 辅助打印函数
void print_list(ds_list *list) {
    printf("List (Size: %zu): [ ", list->size);
    ds_node *curr = list->head;
    while (curr != NULL) {
        int *val = (int *)curr->data;
        printf("%d ", *val);
        curr = curr->next;
    }
    printf("]\n");
}

int main() {
    printf("=== Start Testing List Remove Logic ===\n");

    ds_list list;
    ds_list_init(&list);

    int data[] = {10, 20, 30, 40, 50};

    // 1. 准备数据: [10, 20, 30, 40, 50]
    for(int i=0; i<5; i++) ds_list_push_back(&list, &data[i]);
    print_list(&list);

    // ---------------------------------------------------------
    // 测试 A: 删除中间节点 (删除 index 2 -> 30)
    // 预期: [10, 20, 40, 50]
    // ---------------------------------------------------------
    printf("Test A: Remove Middle (Index 2)...\n");
    ds_list_remove_at_i(&list, 2);
    
    assert(list.size == 4);
    assert(*(int*)list.head->next->next->data == 40); // 20 的下一个应该是 40
    assert(*(int*)list.tail->prev->prev->data == 20); // 40 的上一个应该是 20
    printf("[PASS] Middle Remove\n");

    // ---------------------------------------------------------
    // 测试 B: 删除头部 (删除 index 0 -> 10)
    // 预期: [20, 40, 50]
    // ---------------------------------------------------------
    printf("Test B: Remove Head (Index 0)...\n");
    ds_list_remove_at_i(&list, 0);

    assert(list.size == 3);
    assert(*(int*)list.head->data == 20);
    // 💥 关键检查：新头部的 prev 必须是 NULL
    // 如果你的代码没置空，这里就会崩或者断言失败
    assert(list.head->prev == NULL); 
    printf("[PASS] Head Remove\n");

    // ---------------------------------------------------------
    // 测试 C: 删除尾部 (删除 index 2 -> 50)
    // 预期: [20, 40]
    // ---------------------------------------------------------
    printf("Test C: Remove Tail (Index 2)...\n");
    ds_list_remove_at_i(&list, 2); // 注意现在的 size 是 3，所以最后一个 index 是 2

    assert(list.size == 2);
    assert(*(int*)list.tail->data == 40);
    // 💥 关键检查：新尾部的 next 必须是 NULL
    assert(list.tail->next == NULL);
    printf("[PASS] Tail Remove\n");

    // ---------------------------------------------------------
    // 测试 D: 删除直到空
    // ---------------------------------------------------------
    printf("Test D: Clear remaining...\n");
    ds_list_remove_at_i(&list, 0); // 删 20
    ds_list_remove_at_i(&list, 0); // 删 40
    
    assert(list.size == 0);
    assert(list.head == NULL);
    assert(list.tail == NULL);
    printf("[PASS] Clear All\n");

    // ---------------------------------------------------------
    // 测试 E: 越界测试
    // ---------------------------------------------------------
    printf("Test E: Out of bounds...\n");
    ds_list_remove_at_i(&list, 100); // 应该无事发生
    assert(list.size == 0);     // size 还是 0
    printf("[PASS] Out of bounds\n");

    ds_list_free(&list);
    printf("\n*** ALL TESTS PASSED ***\n");
    return 0;
}