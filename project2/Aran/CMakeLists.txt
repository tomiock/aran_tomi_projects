cmake_minimum_required(VERSION 3.22)

project(
    "project2"
    VERSION 0.1.0
    LANGUAGES C
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(USE_SMALL "Use small" ON)
option(USE_OWN_SMALL "Use own_small" OFF)

set(DATASET_DEFINITIONS)

if (USE_SMALL)
    list(APPEND DATASET_DEFINITIONS -DSMALL)
endif()

if (USE_OWN_SMALL)
    list(APPEND DATASET_DEFINITIONS -DOWN_SMALL)
endif()

set(SOURCES gen_tree.c stack.c queue.c dataset.c)

add_library(stack SHARED stack.c)
add_library(queue SHARED queue.c)
add_library(dataset SHARED dataset.c)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(app gen_tree.c)

target_link_libraries(app stack queue dataset)
target_compile_definitions(app PRIVATE ${DATASET_DEFINITIONS})
