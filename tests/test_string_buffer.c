#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "string_buffer.h"

int main() {
    printf("=== Start Testing StringBuffer ===\n");

    // 1. 初始化
    ds_string sb;
    ds_string_init(&sb);
    
    assert(ds_string_length(&sb) == 0);
    assert(strcmp(ds_string_c_str(&sb), "") == 0);
    printf("[PASS] Init\n");

    // 2. 基础拼接 Append
    ds_string_append(&sb, "Hello");
    ds_string_append(&sb, ", ");
    ds_string_append(&sb, "World");
    
    printf("Result: %s\n", ds_string_c_str(&sb));
    assert(strcmp(ds_string_c_str(&sb), "Hello, World") == 0);
    assert(ds_string_length(&sb) == 12);
    printf("[PASS] Append String\n");

    // 3. 拼接字符和数字
    ds_string_append_char(&sb, '!');
    ds_string_append(&sb, " Count: ");
    ds_string_append_int(&sb, 123);

    printf("Result: %s\n", ds_string_c_str(&sb)); // "Hello, World! Count: 123"
    
    // 验证内容
    const char *expected = "Hello, World! Count: 123";
    assert(strcmp(ds_string_c_str(&sb), expected) == 0);
    printf("[PASS] Append Char & Int\n");

    // 4. 压力测试 (触发自动扩容)
    // 当前 capacity 应该是 32，我们塞点长东西进去
    ds_string_clear(&sb); // 重置
    
    printf("Appending long string to trigger resize...\n");
    for (int i = 0; i < 100; i++) {
        ds_string_append(&sb, "a");
    }
    assert(ds_string_length(&sb) == 100);
    assert(sb.capacity >= 101); // 必须扩容过
    printf("[PASS] Auto Resize\n");

    // 5. 销毁
    ds_string_free(&sb);
    assert(sb.str == NULL);
    printf("[PASS] Free\n");

    printf("\n*** ALL STRING TESTS PASSED ***\n");
    return 0;
}