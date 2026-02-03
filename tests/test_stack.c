#include <stdio.h>
#include <assert.h>
#include "stack.h"

int main() {
    printf("=== Start Testing Stack ===\n");

    // 1. 初始化
    ds_stack s;
    ds_stack_init(&s);
    
    // 检查初始状态
    assert(ds_stack_empty(&s) == true);
    assert(ds_stack_size(&s) == 0);
    assert(ds_stack_top(&s) == NULL); // 空栈取栈顶应为 NULL
    printf("[PASS] Init & Empty Check\n");

    // 准备测试数据
    int data[] = {10, 20, 30, 40, 50};

    // 2. 压栈 (Push) - 放入 10, 20, 30
    printf("Pushing: 10 -> 20 -> 30\n");
    ds_stack_push(&s, &data[0]); 
    ds_stack_push(&s, &data[1]); 
    ds_stack_push(&s, &data[2]); 

    assert(ds_stack_size(&s) == 3);
    assert(ds_stack_empty(&s) == false);
    
    // 检查栈顶现在是不是 30
    int *top = (int *)ds_stack_top(&s);
    assert(*top == 30);
    printf("[PASS] Push\n");

    // 3. 弹栈 (Pop) - 验证顺序是否为 30 -> 20 -> 10
    
    // 第一次弹出的应该是 30
    ds_stack_pop(&s); 
    top = (int *)ds_stack_top(&s);
    assert(*top == 20); // 现在顶变成 20 了吗？
    printf("Popped 30, new top is 20.\n");

    // 第二次弹出的应该是 20
    ds_stack_pop(&s);
    top = (int *)ds_stack_top(&s);
    assert(*top == 10); // 现在顶变成 10 了吗？
    printf("Popped 20, new top is 10.\n");

    // 第三次弹出的应该是 10
    ds_stack_pop(&s);
    assert(ds_stack_empty(&s) == true); // 现在应该空了
    printf("Popped 10, stack is empty.\n");
    
    printf("[PASS] Pop (LIFO Logic)\n");

    // 4. 边界测试：对空栈操作
    ds_stack_pop(&s); // 应该什么都不发生，不会崩溃
    assert(ds_stack_top(&s) == NULL);
    printf("[PASS] Empty Stack Safety\n");

    // 5. 释放
    ds_stack_free(&s);
    printf("[PASS] Free\n");

    printf("\n*** ALL STACK TESTS PASSED ***\n");
    return 0;
}