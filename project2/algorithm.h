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

#include <stdio.h>
#include <stdlib.h>

#include "dijkstra.h"
#include "graph.h"

void algorithm(short src, short dest, struct RoadMap *roadMap);

void makeTrip(struct RoadMap * total_roadMap, short *arr);

#endif // ALGORITHM_H
