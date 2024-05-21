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
    printf("BFS -> Names:\n");
    Print_Tree_BFS(&root_bfs);

    int *arr = Travel_Tree_BFS(&root_bfs);
    int num_trav = 0;

    for(int i = 0; i<NUMBER_CITIES; i++ ){
        if(arr[i+1] != (-1)){
            num_trav++;
        }
    } 

    int **total_path = malloc(sizeof(int*)*num_trav);
    int total_cost = 0;

    int *path_instance;

    for(int i = 0; i<num_trav; i++){
        path_instance = malloc(sizeof(int)*NUMBER_CITIES);
        total_path[i] = path_instance;
    }

    struct RoadMap *roadMap = malloc(sizeof(struct RoadMap));
    printf("Partial road map:\n");
    for(int i = 0; i<NUMBER_CITIES; i++ ){
        if(arr[i+1] != (-1)){
            algorithm(arr[i], arr[i+1], roadMap, total_path, i, &total_cost);
        }
    }   

    printf("\nTotal Road Map:\n");
    int i = 0, j = 0;
    while(i<num_trav){
        j = 0;
        while(total_path[i][j] != -1){
            if(total_path[i][j] != -1)
                printf("%s-", citiesInfo[total_path[i][j]].city_name);
            else j = NUMBER_CITIES;
            j++;
        } 
        i++;
    }
    printf("%s\n", citiesInfo[arr[num_trav]].city_name);

    printf("\nTotal cost: %d\n", total_cost);

    printf("\n----------------------------------\n");

    // DFS
    Def_Node(&root_dfs, 0);
    New_Nodes(&root_dfs);
    DFS(&root_dfs);
    printf("DFS -> Names:\n");
    Print_Tree_DFS(&root_dfs);

    arr = Travel_Tree_DFS(&root_dfs);
    num_trav = 0;

    for(int i = 0; i<NUMBER_CITIES; i++ ){
        if(arr[i+1] != (-1)){
            num_trav++;
        }
    } 

    total_cost = 0;

    for(int i = 0; i<num_trav; i++){
        path_instance = malloc(sizeof(int)*NUMBER_CITIES);
        total_path[i] = path_instance;
    }

    printf("Partial road map:\n");
    for(int i = 0; i<NUMBER_CITIES; i++ ){
        if(arr[i+1] != (-1)){
            algorithm(arr[i], arr[i+1], roadMap, total_path, i, &total_cost);
        }
    }   

    printf("\nTotal Road Map:\n");
    i = 0, j = 0;
    while(i<num_trav){
        j = 0;
        while(total_path[i][j] != -1){
            if(total_path[i][j] != -1)
                printf("%s-", citiesInfo[total_path[i][j]].city_name);
            else j = NUMBER_CITIES;
            j++;
        } 
        i++;
    }
    printf("%s\n", citiesInfo[arr[num_trav]].city_name);

    printf("\nTotal cost: %d\n", total_cost);    

    return 0;
}
