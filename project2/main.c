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
    short bfs_arr[NUMBER_CITIES];
    Travel_Tree_BFS(root_bfs, bfs_arr);
    Free_Tree(root_bfs); // Freeing tree

    struct RoadMap *total_roadMap_bfs = malloc(sizeof(struct RoadMap));
    printf("Partial road map:\n");

    makeTrip(total_roadMap_bfs, bfs_arr);

    printf("\n----------------------------------\n");

    // DFS
    Def_Node(root_dfs, 0); // we asume that the root is the city 0
    New_Nodes(root_dfs);
    DFS(root_dfs);
    printf("DFS -> Names:\n");
    Print_Tree_DFS(root_dfs);

    // Calculating best trip
    short dfs_arr[NUMBER_CITIES];
    Travel_Tree_DFS(root_dfs, dfs_arr);
    Free_Tree(root_dfs);

    struct RoadMap *total_roadMap_dfs = malloc(sizeof(struct RoadMap));
    total_roadMap_dfs->next = NULL;
    printf("\nPartial road map:\n");

    makeTrip(total_roadMap_dfs, dfs_arr);

    return 0;
}
