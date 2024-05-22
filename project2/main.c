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

// Define what algotihm to use **
#define ALGORITHM DIJKSTRAS

int main (void) {
    // Choose wich dataset to import depending on the compilation
    #ifdef DATASET_SMALL
        #include "datasets/small.h"
        printf("This is a small case of the program\n\n");
    #elif defined(DATASET_MEDIUM)
        #include "datasets/medium.h"
        printf("This is a medium case of the program\n\n");
    #elif defined(DATASET_LARGE)
        #include "datasets/large.h"
        printf("This is a large case of the program\n\n");
    #else
        #error "No dataset size defined"
    #endif

    struct FamilyTreeNode root_dfs;
    struct FamilyTreeNode root_bfs;

    printf("Ancestors’ tree:\n\n");

    // BFS
    // Creating tree
    Def_Node(&root_bfs, 0);
    New_Nodes(&root_bfs);
    BFS(&root_bfs);

    // Printing tree
    printf("BFS -> Names:\n");
    Print_Tree_BFS(&root_bfs);

    // Calculating best trip
    int *arr = Travel_Tree_BFS(&root_bfs);
    struct RoadMap *total_roadMap_bfs = malloc(sizeof(struct RoadMap));
    printf("Partial road map:\n");

    makeTrip(&total_roadMap_bfs, arr);

    printf("\nTotal Road Map:\n");
    printTOTALRoadMap(total_roadMap_bfs);

    printf("\n----------------------------------\n");

    // DFS
    Def_Node(&root_dfs, 0);
    New_Nodes(&root_dfs);
    DFS(&root_dfs);
    printf("DFS -> Names:\n");
    Print_Tree_DFS(&root_dfs);

    // Calculating best trip
    int *dfs_arr = Travel_Tree_DFS(&root_dfs);
    struct RoadMap *total_roadMap_dfs = malloc(sizeof(struct RoadMap));
    printf("Partial road map:\n");

    makeTrip(&total_roadMap_dfs, dfs_arr);  

    printf("\nTotal Road Map:\n");
    printTOTALRoadMap(total_roadMap_dfs);

    return 0;
}
