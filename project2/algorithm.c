#include "algorithm.h"

// Define what algotihm to use **
#define ALGORITHM DIJKSTRAS

// Create the enum for choosing the algorithm
enum { DIJKSTRAS = 0, A_STAR = 1 };

void makeTrip(struct RoadMap *total_roadMap, short *arr) {
    for (int i = 0; i < NUMBER_CITIES - 1; i++) {
        struct RoadMap *partial_roadMap = malloc(sizeof(struct RoadMap));
        partial_roadMap->next = NULL;

        if (arr[i + 1] != (-1)) {

            switch (ALGORITHM) {
            case DIJKSTRAS:
                dijkstra_matrix(adjacency_matrix, arr[i], arr[i + 1],
                                partial_roadMap);
                break;
            case A_STAR:
                break;
            }

            printRoadMap(partial_roadMap);
        }

        if (i == 0) {
            total_roadMap = partial_roadMap;
        } else {
            appendRoadMap(total_roadMap, partial_roadMap);
        }
    }
}
