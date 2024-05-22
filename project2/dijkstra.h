#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#ifdef DATASET_SMALL
    #include "datasets/small.h"
#elif defined(DATASET_MEDIUM)
    #include "datasets/medium.h"
#elif defined(DATASET_LARGE)
    #include "datasets/large.h"
#else
    #error "No dataset size defined"
#endif

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void printSolution(int dist[], int parent[], int src, int dest);

void printPath(int parent[], int j);

int min_distance(int distances[], bool visited_set[]);

void dijkstra(int graph[NUMBER_CITIES][NUMBER_CITIES], int src, int dest, struct RoadMap *roadMap);

#endif // DIJKSTRA_H

