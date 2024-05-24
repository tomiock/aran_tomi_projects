// Import our headers:
#include "algorithm.h"
#include "datasets/small.h"
#include "graph.h"
#include "queue.h"
#include "stack.h"
#include "stdio.h"
#include "tree.h"

// Define what algotihm to use **
#define ALGORITHM DIJKSTRAS

int main(void) {

    struct FamilyTreeNode * root_dfs = malloc(sizeof(struct FamilyTreeNode));
    struct FamilyTreeNode * root_bfs = malloc(sizeof(struct FamilyTreeNode));

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
    short bfs_arr[NUMBER_CITIES];
    Travel_Tree_BFS(root_bfs, bfs_arr);
    Free_Tree(root_bfs);

    struct RoadMap *total_roadMap_bfs = malloc(sizeof(struct RoadMap));
    total_roadMap_bfs->next = NULL;
    printf("Partial road map:\n");

    makeTrip(total_roadMap_bfs, bfs_arr);

    printf("\nTotal Road Map:\n");
    printTOTALRoadMap(total_roadMap_bfs);
    
    // FREE
    FreeRoadMap(total_roadMap_bfs);
    Free_Tree(root_bfs);
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
    Free_Tree(root_dfs);

    struct RoadMap *total_roadMap_dfs = malloc(sizeof(struct RoadMap));
    total_roadMap_dfs->next = NULL;
    printf("\nPartial road map:\n");

    makeTrip(total_roadMap_dfs, dfs_arr);
    free(dfs_arr);

    printf("\nTotal Road Map:\n");
    printTOTALRoadMap(total_roadMap_dfs);
    
    // FREE
    freeRoadMap(total_roadMap_dfs);

    return 0;
}
