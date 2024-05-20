#include "small.h"

#ifndef GRAPH_H
#define GRAPH_H

struct City {
    unsigned int id;
    unsigned int num_neighbors;
    struct Neighbor **neighbors;
};

struct Neighbor {
    unsigned int id;
    unsigned int distance;
};

void print_adjacency_matrix(int matrix[NUMBER_CITIES][NUMBER_CITIES]);

void matrix_to_list(int matrix[NUMBER_CITIES][NUMBER_CITIES], struct City * list[NUMBER_CITIES]);

void free_cities_list(struct City * list[NUMBER_CITIES]);

#endif // GRAPH_H
