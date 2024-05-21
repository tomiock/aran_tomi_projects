#ifdef DATASET_SMALL
    #include "datasets/small.h"
#elif defined(DATASET_MEDIUM)
    #include "datasets/medium.h"
#elif defined(DATASET_LARGE)
    #include "datasets/large.h"
#else
    #error "No dataset size defined"
#endif

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

void search_path(struct City *cities[NUMBER_CITIES], void *start, void *end, struct RoadMap * map);

#endif // GRAPH_H
