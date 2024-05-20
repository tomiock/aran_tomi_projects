#include "small.h"

#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "small.h"

void printSolution(int dist[], int parent[], int src, int dest);

void printPath(int parent[], int j);

int min_distance(int dist[], int sptSet[], int V);

void dijkstra(int graph[NUMBER_CITIES][NUMBER_CITIES], int src, int dest);

#endif // DIJKSTRA_H

