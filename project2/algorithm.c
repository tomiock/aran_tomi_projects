#include "algorithm.h"

// Define what algotihm to use **
#define ALGORITHM DIJKSTRAS

// Create the enum for choosing the algorithm
enum { DIJKSTRAS = 0, A_STAR = 1 };

void algorithm(short src, short dest, struct RoadMap *roadMap) {
    switch (ALGORITHM) {
    case DIJKSTRAS:
        dijkstra_matrix(adjacency_matrix, src, dest, roadMap);
        break;

    case A_STAR:
        break;
    }
}

void makeTrip(struct RoadMap * total_roadMap, short *arr) {
    for (int i = 0; i < NUMBER_CITIES; i++) {
        struct RoadMap *partial_roadMap = malloc(sizeof(struct RoadMap));
        if (arr[i + 1] != (-1)) {
            algorithm(arr[i], arr[i + 1], partial_roadMap);
            printRoadMap(partial_roadMap);
        }

        if (i == 0) {
            *total_roadMap = *partial_roadMap;
        } else {
            appendRoadMap(total_roadMap, partial_roadMap);
        }  
    } 
}
