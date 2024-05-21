#include "algorithm.h"

// Define what algotihm to use **
#define ALGORITHM DIJKSTRAS

// Create the enum for choosing the algorithm
enum {DIJKSTRAS = 0, A_STAR = 1 };

void algorithm(int src, int dest, struct RoadMap *roadMap){
    switch (ALGORITHM) {
            case DIJKSTRAS:
                printf("\nUsing Dijkstra's Algorithm\n");
                dijkstra(adjacency_matrix, src, dest, roadMap); // 0 is the source, 9 is the destination
                break;

            case A_STAR:
                printf("\nUsing A* Algorithm\n");

                struct City *cities_list[NUMBER_CITIES] = {NULL};
                matrix_to_list(adjacency_matrix, cities_list);

                for (int i = 0; i < NUMBER_CITIES; i++) {
                    printf("City %d:\n", cities_list[i]->id);
                    for (unsigned int j = 0; j < cities_list[i]->num_neighbors; j++) {
                        printf("  Neighbor %d, Distance %d\n", cities_list[i]->neighbors[j]->id, cities_list[i]->neighbors[j]->distance);
                    }
                }

                printf("ERROR Not implemented yet\n");
                free_cities_list(cities_list);
                break;
        }

        printf("Total cost of the road map: %d\n", roadMap->total_cost); // check
        while (roadMap->next != NULL) {
            printf("Current Node: %d\n", roadMap->city_id);
            roadMap = roadMap->next;
        }
}