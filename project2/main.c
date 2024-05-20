#include "small.h"
#include "dijkstra.h"
#include "graph.h"
#include "stdio.h"

#define NUMBER_CITIES 10
#define MAX_NAME 10
#define MAX_CITY_NAME 20

#define ALGORITHM A_STAR

enum {DIJKSTRAS = 0, A_STAR = 1 };

int main (void) {
    print_adjacency_matrix(adjacency_matrix);

    struct City *cities_list[NUMBER_CITIES] = {NULL};

    matrix_to_list(adjacency_matrix, cities_list);

    for (int i = 0; i < NUMBER_CITIES; i++) {
        printf("City %d:\n", cities_list[i]->id);
        for (unsigned int j = 0; j < cities_list[i]->num_neighbors; j++) {
            printf("  Neighbor %d, Distance %d\n", cities_list[i]->neighbors[j]->id, cities_list[i]->neighbors[j]->distance);
        }
    }

    free_cities_list(cities_list);

    switch (ALGORITHM) {
        case DIJKSTRAS:
            printf("\nUsing Dijkstra's Algorithm\n");
            dijkstra(adjacency_matrix, 0, 9); // 0 is the source, 9 is the destination
            break;
        case A_STAR:
            printf("\nUsing A* Algorithm\n");
            printf("ERROR Not implemented yet\n");
            break;
    }

    return 0;
}
