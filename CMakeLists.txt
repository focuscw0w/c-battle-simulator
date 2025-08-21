cmake_minimum_required(VERSION 3.27)
project(z4 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -fno-omit-frame-pointer -g")
add_compile_options(-Wall -Wextra -Wuninitialized -pedantic -g)

add_executable(z4 src/data.c src/z4.c)
target_include_directories(z4 PRIVATE include)
target_link_libraries(z4 -lm)





