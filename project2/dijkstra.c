#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "dijkstra.h"

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

int minDistance(int dist[], bool sptSet[]) {
  int min = INT_MAX, min_index;
  for (int v = 0; v < V; v++)
    if (!sptSet[v] && dist[v] <= min)
      min = dist[v], min_index = v;
  return min_index;
}

void dijkstra(int graph[NUMBER_CITIES][NUMBER_CITIES], int src, int dest, struct RoadMap *roadMap) {
  int dist[V];
  bool sptSet[V];
  int path[V]; // used to store the path sequence

  // initialize the distances to the nodes at infinity and path at -1
  for (int i = 0; i < V; i++) {
    dist[i] = INT_MAX;
    sptSet[i] = false;
    path[i] = -1;
  }

  dist[src] = 0;

  for (int count = 0; count < V - 1; count++) {
    int u = minDistance(dist, sptSet);
    if (u == dest) {
      break; // stop if the destination is reached
    }
    sptSet[u] = true;

    for (int v = 0; v < V; v++) {
      if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX &&
          dist[u] + graph[u][v] < dist[v]) {
        dist[v] = dist[u] + graph[u][v];
        path[v] = u;
      }
    }
  }

  // construct the path from src to dest using the path array
  int stack[V];
  int stack_index = 0;
  int current = dest;

  while (current != -1 && current != src) {
    stack[stack_index++] = current;
    current = path[current];
  }

  if (current == src) {
    stack[stack_index++] = src;

    // reverse the stack to get the path from src to dest
    for (int i = 0; i < stack_index / 2; i++) {
      int temp = stack[i];
      stack[i] = stack[stack_index - i - 1];
      stack[stack_index - i - 1] = temp;
    }

    // populate the RoadMap structure
    struct RoadMap *currentRoadMap = roadMap; // define a new variables to populate the struct
    // we need to keep the head of the struct to "return it"
    for (int i = 0; i < stack_index; i++) {
      currentRoadMap->city_id = stack[i];
      currentRoadMap->total_cost = dist[dest];
      if (i < stack_index - 1) {
        currentRoadMap->next = (struct RoadMap *)malloc(sizeof(struct RoadMap));
        currentRoadMap = currentRoadMap->next;
      } else {
        currentRoadMap->next = NULL; // final roadmap null
      }
    }
  } else {
    printf("No path found from src to dest\n");
  }
}
