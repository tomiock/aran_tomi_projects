// Import the standard libraries:
#include <stdio.h>
#include <stdlib.h>

// Import our headers:
#include "graph.h"
#include "stdio.h"
#include "stack.h"
#include "queue.h"
#include "tree.h"
#include "algorithm.h"

// Choose wich dataset to import depending on the compilation
#ifdef DATASET_SMALL
    #include "datasets/small.h"
#elif defined(DATASET_MEDIUM)
    #include "datasets/medium.h"
#elif defined(DATASET_LARGE)
    #include "datasets/large.h"
#else
    #error "No dataset size defined"
#endif

// Define what algotihm to use **
#define ALGORITHM DIJKSTRAS

int main (void) {
    struct FamilyTreeNode root_dfs;
    struct FamilyTreeNode root_bfs;

    printf("Ancestors’ tree:\n\n");

    // BFS
    Def_Node(&root_bfs, 0);
    New_Nodes(&root_bfs);
    BFS(&root_bfs);
    printf("BFS -> Names:\n");
    Print_Tree_BFS(&root_bfs);

    int *arr = Travel_Tree_BFS(&root_bfs);

    struct RoadMap *total_roadMap_bfs = malloc(sizeof(struct RoadMap));

    printf("Partial road map:\n");
    for(int i = 0; i<NUMBER_CITIES; i++ ){
        struct RoadMap *partial_roadMap = malloc(sizeof(struct RoadMap));
        if(arr[i+1] != (-1)){
            algorithm(arr[i], arr[i+1], partial_roadMap);
            printRoadMap(partial_roadMap);
        }

       if(i == 0){
            total_roadMap_bfs = partial_roadMap;
        } else {
            appendRoadMap(total_roadMap_bfs, partial_roadMap);
        }
    }   

    printf("\nTotal Road Map:\n");
    printTOTALRoadMap(total_roadMap_bfs);

    printf("\n----------------------------------\n");

    // DFS
    Def_Node(&root_dfs, 0);
    New_Nodes(&root_dfs);
    DFS(&root_dfs);
    printf("DFS -> Names:\n");
    Print_Tree_DFS(&root_dfs);

    arr = Travel_Tree_DFS(&root_dfs);

    struct RoadMap *total_roadMap_dfs = malloc(sizeof(struct RoadMap));

    printf("Partial road map:\n");
    for(int i = 0; i<NUMBER_CITIES; i++ ){
        struct RoadMap *partial_roadMap = malloc(sizeof(struct RoadMap));
        if(arr[i+1] != (-1)){
            algorithm(arr[i], arr[i+1], partial_roadMap);
            printRoadMap(partial_roadMap);
        }

        if (i == 0){
            total_roadMap_dfs = partial_roadMap;
        } else {
            appendRoadMap(total_roadMap_dfs, partial_roadMap);
        }
    }   

    printf("\nTotal Road Map:\n");
    printTOTALRoadMap(total_roadMap_dfs);

    return 0;
}
