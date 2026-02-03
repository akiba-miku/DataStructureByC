#include <stdio.h>
#include <assert.h>
#include "vector.h"

// Helper: print vector state
void print_vector(ds_vector *v) {
    printf("Vector (Size: %d, Cap: %d): [ ", v->size, v->capacity);
    for (int i = 0; i < v->size; i++) {
        // cast void* back to int* to print value
        int *val = (int *)ds_vector_get(v, i);
        printf("%d ", *val);
    }
    printf("]\n");
}

int main() {
    printf("=== Start Testing ds_vector ===\n");

    // 1. Initialize
    ds_vector v;
    ds_vector_init(&v, 2); // Start small to test resize
    assert(v.size == 0);
    assert(v.capacity == 2);
    printf("[PASS] Init\n");

    // 2. Prepare data (on stack)
    int data[] = {10, 20, 30, 40, 50};

    // 3. Test Add & Resize
    ds_vector_add(&v, &data[0]); 
    ds_vector_add(&v, &data[1]); 
    ds_vector_add(&v, &data[2]); // Trigger resize here (3 > 2)
    
    assert(v.size == 3);
    assert(v.capacity > 2); 
    print_vector(&v);
    printf("[PASS] Add & Resize\n");

    // 4. Test Get
    int *val = (int *)ds_vector_get(&v, 1);
    assert(*val == 20);
    printf("[PASS] Get\n");

    // 5. Test Set
    ds_vector_set(&v, 1, &data[4]); // Change index 1 (20) to 50
    val = (int *)ds_vector_get(&v, 1);
    assert(*val == 50);
    printf("[PASS] Set\n");

    // 6. Test Remove (Middle)
    // Current: [10, 50, 30] -> Remove index 1 (50) -> Expect: [10, 30]
    ds_vector_remove_at_i(&v, 1);
    assert(v.size == 2);
    assert(*(int*)ds_vector_get(&v, 1) == 30); // 30 should shift to index 1
    printf("[PASS] Remove Middle\n");

    // 7. Test Remove (Head)
    // Current: [10, 30] -> Remove index 0 (10) -> Expect: [30]
    ds_vector_remove_at_i(&v, 0);
    assert(v.size == 1);
    assert(*(int*)ds_vector_get(&v, 0) == 30);
    printf("[PASS] Remove Head\n");

    // 8. Free
    ds_vector_free(&v);
    assert(v.data == NULL);
    assert(v.size == 0);
    printf("[PASS] Free\n");

    printf("\n*** ALL TESTS PASSED ***\n");
    return 0;
}