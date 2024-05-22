#include "algorithm.h"

// Define what algotihm to use **
#define ALGORITHM DIJKSTRAS

// Create the enum for choosing the algorithm
enum {DIJKSTRAS = 0, A_STAR = 1 };

void algorithm(int src, int dest, struct RoadMap *roadMap){
    switch (ALGORITHM) {
            case DIJKSTRAS:
                dijkstra(adjacency_matrix, src, dest, roadMap); // 0 is the source, 9 is the destination
                break;

            case A_STAR:
                break;
        }
}
