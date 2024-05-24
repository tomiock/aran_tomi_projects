// Import the standard libraries:
#include <stdio.h>
#include <stdlib.h>

// Import our headers:
#include "algorithm.h"
#include "graph.h"
#include "queue.h"
#include "stack.h"
#include "stdio.h"
#include "tree.h"

// Define what algotihm to use **
#define ALGORITHM DIJKSTRAS

int main(void) {
    // Choose which dataset to import depending on the compilation
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

    struct FamilyTreeNode *root_dfs = malloc(sizeof(struct FamilyTreeNode));
    struct FamilyTreeNode *root_bfs = malloc(sizeof(struct FamilyTreeNode));

    printf("Ancestors’ tree:\n\n");

    // BFS
    // Creating tree
    Def_Node(root_bfs, 0);
    New_Nodes(root_bfs);
    BFS(root_bfs);

    // Printing tree
    printf("BFS -> Names:\n");
    Print_Tree_BFS(root_bfs);

    // Calculating best trip
    int *bfs_arr = Travel_Tree_BFS(root_bfs);
    struct RoadMap *total_roadMap_bfs = malloc(sizeof(struct RoadMap));
    total_roadMap_bfs->next = NULL;
    printf("Partial road map:\n");

    makeTrip(&total_roadMap_bfs, bfs_arr);

    printf("\nTotal Road Map:\n");
    printTOTALRoadMap(total_roadMap_bfs);
    
    // FREE
    FreeRoadMap(total_roadMap_bfs);
    //Free_Tree(&root_bfs);
    FreeTravelTree(bfs_arr);

    printf("\n----------------------------------\n");

    // DFS
    Def_Node(root_dfs, 0);
    New_Nodes(root_dfs);
    DFS(root_dfs);
    printf("DFS -> Names:\n");
    Print_Tree_DFS(root_dfs);

    // Calculating best trip
    int *dfs_arr = Travel_Tree_DFS(root_dfs);
    struct RoadMap *total_roadMap_dfs = malloc(sizeof(struct RoadMap));
    total_roadMap_dfs->next = NULL;
    printf("\nPartial road map:\n");

    makeTrip(&total_roadMap_dfs, dfs_arr);

    printf("\nTotal Road Map:\n");
    printTOTALRoadMap(total_roadMap_dfs);
    Print_Tree_DFS(root_dfs);
    // FREE
    FreeRoadMap(total_roadMap_dfs);
    Free_Tree(root_dfs);
    FreeTravelTree(dfs_arr);

    return 0;
}
