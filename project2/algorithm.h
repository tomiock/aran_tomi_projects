#ifdef DATASET_SMALL
    #include "datasets/small.h"
#elif defined(DATASET_MEDIUM)
    #include "datasets/medium.h"
#elif defined(DATASET_LARGE)
    #include "datasets/large.h"
#else
    #error "No dataset size defined"
#endif

#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <stdlib.h>
#include <stdio.h>

#include "graph.h"
#include "dijkstra.h"

void algorithm(int src, int dest, struct RoadMap *roadMap, int **total_path, int path_num, int *total_cost);

#endif // ALGORITHM_H