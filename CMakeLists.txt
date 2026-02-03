cmake_minimum_required(VERSION 3.10)
project(DataStructureByC C)

# 1. 设置编译选项
add_compile_options(-Wall -Wextra -g)

# 2. 包含头文件路径 (让所有源文件都能找到 .h)
include_directories(include)

# ==========================================
# 核心动作：生成静态库 (libds_core.a)
# ==========================================
# 把 src 下的所有 .c 文件编译成一个库
# 以后你有新模块（比如 stack.c, queue.c），加到这里即可
add_library(ds_core STATIC
    src/vector.c
    src/list.c
    src/stack.c
    src/queue.c
)

# ==========================================
# 生成测试程序
# ==========================================

# # 测试 1: Vector (原来的 main.c)
# add_executable(test_vector tests/test_vector.c)
# # 关键：告诉编译器，test_vector 需要用到 ds_core 里的函数
# target_link_libraries(test_vector ds_core)

# 测试 2: List (新的链表测试)
add_executable(test_list tests/test_list.c)
target_link_libraries(test_list ds_core)

add_executable(test_stack tests/test_stack.c)
target_link_libraries(test_stack ds_core)

add_executable(test_queue tests/test_queue.c)
target_link_libraries(test_queue ds_core)