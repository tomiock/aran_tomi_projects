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

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

void printSolution(int dist[], int parent[], int src, int dest);

void printPath(int parent[], int j);

short min_distance(short distances[], bool visited_set[]);

void dijkstra_matrix(const unsigned short graph[NUMBER_CITIES][NUMBER_CITIES], unsigned short src, unsigned short dest,
                     struct RoadMap *roadMap);
void freeDijkstra();

void dijikstra_list(struct City * cities_list[NUMBER_CITIES], unsigned short src, unsigned short dest);

#endif // DIJKSTRA_H
