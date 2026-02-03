cmake_minimum_required(VERSION 3.10)

project(DataStructureByC C)

include_directories(include)
add_compile_options(-Wall -Wextra -g)

add_executable(main 
    src/main.c 
    src/vector.c
)