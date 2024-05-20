#include "small.h"
#include "dijkstra.h"
#include "graph.h"
#include "stdio.h"

#define NUMBER_CITIES 10
#define MAX_NAME 10
#define MAX_CITY_NAME 20

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

    dijkstra(adjacency_matrix, 0, 9); // 0 is the source, 9 is the destination

    return 0;
}
