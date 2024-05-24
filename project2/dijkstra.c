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

int min_distance(int distances[], bool visited_set[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (!visited_set[v] && distances[v] <= min)
            min = distances[v], min_index = v;
    return min_index;
}

void dijkstra_matrix(int graph[NUMBER_CITIES][NUMBER_CITIES], int src, int dest, struct RoadMap *roadMap) {
    int distances[V];
    bool visited_set[V];
    int path[V]; // used to store the path sequence

    // initialize the distances to the nodes at infinity and path at -1
    for (int i = 0; i < V; i++) {
        distances[i] = INT_MAX;
        visited_set[i] = false;
        path[i] = -1;
    }

    distances[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = min_distance(distances, visited_set);
        if (u == dest) {
            break; // stop if the destination is reached
        }
        visited_set[u] = true;

        for (int v = 0; v < V; v++) {
            if (!visited_set[v] && graph[u][v] && distances[u] != INT_MAX &&
                distances[u] + graph[u][v] < distances[v]) {
                distances[v] = distances[u] + graph[u][v];
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
        roadMap->total_cost = 0;
        struct RoadMap *currentRoadMap = roadMap; // define a new variable to populate the struct
        currentRoadMap->next = NULL;
        // we need to keep the head of the struct to "return it"
        for (int i = 0; i < stack_index; i++) {
            currentRoadMap->city_id = stack[i];
            currentRoadMap->total_cost = distances[stack[i]];

            if (i < stack_index - 1) {
                currentRoadMap->next = (struct RoadMap *)malloc(sizeof(struct RoadMap));
                currentRoadMap = currentRoadMap->next;
                currentRoadMap->next = NULL;
            }
        }
    } else {
        printf("No path found from src to dest\n");
    }
}

void freeDijkstra(){

};