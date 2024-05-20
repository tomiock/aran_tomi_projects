cmake_minimum_required(VERSION 3.22)

project(
    "project2"
    VERSION 0.1.0
    LANGUAGES C
)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCES gen_tree.c stack.c queue.c)

add_library(stack SHARED stack.c)
add_library(queue SHARED queue.c)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(app gen_tree.c)

target_link_libraries(app stack queue)

