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

    struct FamilyTreeNode root_dfs;
    struct FamilyTreeNode root_bfs;

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
    short *arr = Travel_Tree_BFS(root_bfs);
    free(root_bfs);
    struct RoadMap *total_roadMap_bfs = malloc(sizeof(struct RoadMap));
    printf("Partial road map:\n");

    makeTrip(total_roadMap_bfs, arr);
    free(arr);

    printf("\nTotal Road Map:\n");
    printTOTALRoadMap(total_roadMap_bfs);
    free(total_roadMap_bfs);
    
    // FREE
    free(total_roadMap_bfs);
    Free_Tree(&root_bfs);
    FreeTravelTree(bfs_arr);

    printf("\n----------------------------------\n");

    // DFS
    Def_Node(root_dfs, 0);
    New_Nodes(root_dfs);
    DFS(root_dfs);
    printf("DFS -> Names:\n");
    Print_Tree_DFS(root_dfs);

    // Calculating best trip
    short *dfs_arr = Travel_Tree_DFS(root_dfs);
    free(root_dfs);

    struct RoadMap *total_roadMap_dfs = malloc(sizeof(struct RoadMap));
    printf("\nPartial road map:\n");

    makeTrip(total_roadMap_dfs, dfs_arr);
    free(dfs_arr);

    printf("\nTotal Road Map:\n");
    printTOTALRoadMap(total_roadMap_dfs);
    
    // FREE
    free(total_roadMap_dfs);
    Free_Tree(&root_dfs);
    FreeTravelTree(dfs_arr);

    return 0;
}
