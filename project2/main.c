// Import the standard libraries:
#include <stdio.h>
#include <stdlib.h>

// Import our headers:
#include "dijkstra.h"
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
    printf("BFS-> Names:\n");
    Print_Tree_BFS(&root_bfs);


    printf("\n----------------------------------\n");

    // DFS
    Def_Node(&root_dfs, 0);
    New_Nodes(&root_dfs);
    DFS(&root_dfs);
    printf("DFS-> Names:\n");
    Print_Tree_DFS(&root_dfs);
    //return 0;
    printf("\nTOMI:\n");

    struct RoadMap *roadMap = malloc(sizeof(struct RoadMap));

    algorithm(0, 9, roadMap);    

    return 0;
}
