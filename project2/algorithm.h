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

void algorithm(int src, int dest, struct RoadMap *roadMap);

void searchTrip(int src, int dest, struct RoadMap *partial_roadMap);

void makeTrip(struct RoadMap **total_roadMap, int *arr);
#endif // ALGORITHM_H
