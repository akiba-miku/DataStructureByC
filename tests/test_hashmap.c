#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "hashmap.h"

// 辅助打印函数
void print_map_stats(ds_hashmap *map) {
    printf("Map Stats -> Size: %zu, Capacity: %zu\n", map->size, map->capacity);
}

int main() {
    printf("=== Start Testing HashMap ===\n");

    // 1. 初始化
    // 故意给一个小容量 (4)，方便快速触发扩容测试
    ds_hashmap map;
    ds_hashmap_init(&map, 4); 
    
    assert(ds_hashmap_size(&map) == 0);
    assert(ds_hashmap_empty(&map) == true);
    printf("[PASS] Init\n");

    // 2. Put (新增)
    int v1 = 100, v2 = 200, v3 = 300;
    
    // 插入 "Alice"
    ds_hashmap_put(&map, "Alice", &v1);
    assert(*(int*)ds_hashmap_get(&map, "Alice") == 100);
    
    // 插入 "Bob"
    ds_hashmap_put(&map, "Bob", &v2);
    assert(*(int*)ds_hashmap_get(&map, "Bob") == 200);

    assert(ds_hashmap_size(&map) == 2);
    printf("[PASS] Put & Get Basic\n");

    // 3. Put (更新 / Update)
    int v1_new = 101;
    ds_hashmap_put(&map, "Alice", &v1_new); // Alice 分数变了
    assert(*(int*)ds_hashmap_get(&map, "Alice") == 101); // 应该是新值
    assert(ds_hashmap_size(&map) == 2); // 大小不变
    printf("[PASS] Update Value\n");

    // 4. 测试扩容 (Resize)
    // 当前容量 4，负载因子 0.75 -> 阈值是 3。
    // 目前有 2 个元素。再加 1 个变成 3，再加 1 个变成 4 -> 触发扩容。
    
    printf("--- Triggering Resize ---\n");
    print_map_stats(&map); // 应该 Cap: 4
    
    int v4 = 400, v5 = 500;
    ds_hashmap_put(&map, "Charlie", &v3);
    ds_hashmap_put(&map, "Dave", &v4);
    ds_hashmap_put(&map, "Eve", &v5); // 第 5 个元素，肯定触发扩容了
    
    print_map_stats(&map); // 应该 Cap > 4 (比如 6 或 8)
    
    assert(map.capacity > 4); 
    assert(ds_hashmap_size(&map) == 5);
    
    // 扩容后，老数据还能找到吗？
    assert(*(int*)ds_hashmap_get(&map, "Alice") == 101);
    assert(*(int*)ds_hashmap_get(&map, "Eve") == 500);
    printf("[PASS] Resize Logic\n");

    // 5. Remove (删除)
    ds_hashmap_remove(&map, "Bob");
    assert(ds_hashmap_get(&map, "Bob") == NULL); // 查不到了
    assert(ds_hashmap_size(&map) == 4);
    printf("[PASS] Remove\n");

    // 6. 边缘测试：查不存在的 Key
    assert(ds_hashmap_get(&map, "Ghost") == NULL);
    
    // 7. 销毁
    ds_hashmap_free(&map);
    assert(map.buckets == NULL); // 确保指针置空 (虽然你的实现没置空 buckets 指针本身，但释放了内存，这里可以手动置空或者检查 size)
    assert(map.size == 0);
    printf("[PASS] Free\n");

    printf("\n*** ALL HASHMAP TESTS PASSED ***\n");
    return 0;
}