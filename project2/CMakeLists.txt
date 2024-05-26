cmake_minimum_required(VERSION 3.22)

project(
    "project2"
    VERSION 0.1.0
    LANGUAGES C
)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set the default values
option(USE_SMALL_DATASET "Use small dataset" OFF)
option(USE_MEDIUM_DATASET "Use medium dataset" OFF)
option(USE_LARGE_DATASET "Use large dataset" OFF)

# ensure the only one macro is engaged at a time
if(USE_SMALL_DATASET AND USE_MEDIUM_DATASET)
    message(FATAL_ERROR "Select one dataset (selected: small and medium)")
endif()
if(USE_SMALL_DATASET AND USE_LARGE_DATASET)
    message(FATAL_ERROR "Select one dataset (selected: small and large)")
endif()
if(USE_MEDIUM_DATASET AND USE_LARGE_DATASET)
    message(FATAL_ERROR "Select one dataset (selected: medium and large)")
endif()
if(NOT USE_SMALL_DATASET AND NOT USE_MEDIUM_DATASET AND NOT USE_LARGE_DATASET)
    message(FATAL_ERROR "Select one dataset (selected: none) e.g.`-DUSE_SMALL_DATASET=ON`")
endif()

if(USE_SMALL_DATASET)
    add_definitions(-DDATASET_SMALL)
elseif(USE_MEDIUM_DATASET)
    add_definitions(-DDATASET_MEDIUM)
elseif(USE_LARGE_DATASET)
    add_definitions(-DDATASET_LARGE)
else()
    message(FATAL_ERROR "You must select exactly one dataset size (USE_SMALL_DATASET, USE_MEDIUM_DATASET, USE_LARGE_DATASET).")
endif()

set(SOURCES main.c graph.c dijkstra.c tree.c stack.c queue.c algorithm.c)

set(CMAKE_C_FLAGS_RELEASE "-O3")

add_library(graph SHARED graph.c)
add_library(dijkstra SHARED dijkstra.c)
add_library(tree SHARED tree.c)
add_library(stack SHARED stack.c)
add_library(queue SHARED queue.c)
add_library(algorithm SHARED algorithm.c)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(algorithm PRIVATE dijkstra)
target_link_libraries(algorithm PRIVATE graph)

add_executable(app main.c)
target_link_libraries(app graph dijkstra tree stack queue algorithm)
