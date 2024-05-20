#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

#include "dijkstra.h"
#include "small.h"

int minDistance(int dist[], bool sptSet[]) {
  // Initialize min value
  int min = INT_MAX, min_index;

  for (int v = 0; v < NUMBER_CITIES; v++)
    if (sptSet[v] == false && dist[v] <= min)
      min = dist[v], min_index = v;

  return min_index;
}

void printSolution(int dist[], int parent[], int src, int dest) {
  printf("Shortest path from %d to %d is: %d ", src, dest, src);
  printPath(parent, dest);
  printf("\nDistance: %d\n", dist[dest]);
}

void printPath(int parent[], int j) {
  if (parent[j] == -1)
    return;
  printPath(parent, parent[j]);
  printf("%d ", j);
}

#define V NUMBER_CITIES

void dijkstra(int graph[V][V], int src, int dest) {
  int dist[V];
  bool sptSet[V];
  int parent[V];

  for (int i = 0; i < V; i++) {
    dist[i] = INT_MAX, sptSet[i] = false;
    parent[i] = -1;
  }

  dist[src] = 0;

  for (int count = 0; count < V - 1; count++) {
    int u = minDistance(dist, sptSet);
    if (u == dest) {
      break; // Stop if the destination is reached
    }
    sptSet[u] = true;

    for (int v = 0; v < V; v++)
      if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX &&
          dist[u] + graph[u][v] < dist[v]) {
        dist[v] = dist[u] + graph[u][v];
        parent[v] = u;
      }
  }

  printSolution(dist, parent, src, dest);
}
