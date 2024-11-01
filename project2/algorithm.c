#include "algorithm.h"

// Define what algotihm to use **
#define ALGORITHM DIJKSTRAS_MATRIX

// Create the enum for choosing the algorithm
enum { DIJKSTRAS_MATRIX = 0, DIJKSTRAS_LIST = 1 };

void makeTrip(struct RoadMap *total_roadMap, short *arr) {
    for (int i = 0; i < NUMBER_CITIES - 1; i++) {
        struct RoadMap *partial_roadMap = malloc(sizeof(struct RoadMap));
        partial_roadMap->next = NULL;

        if (arr[i + 1] != (-1)) {

            switch (ALGORITHM) {
            case DIJKSTRAS_MATRIX:
                dijkstra_matrix(adjacency_matrix, arr[i], arr[i + 1],
                                partial_roadMap);
                break;
            case DIJKSTRAS_LIST:
                break;
            }

            printRoadMap(partial_roadMap);
        }

        if (i == 0) {
            struct RoadMap *temp = total_roadMap;
            total_roadMap = partial_roadMap;
            if(temp!=NULL)
                free(temp);
            temp = NULL;
        } else {
            appendRoadMap(total_roadMap, partial_roadMap);
        }
        
    }
    printf("\nTotal Road Map:\n");
    printTOTALRoadMap(total_roadMap);
    printf("\n");

    freeRoadMap(total_roadMap);
}
