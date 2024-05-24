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

short min_distance(short distances[], bool visited_set[]) {
    short min = SHRT_MAX;
    short min_index;

    for (int v = 0; v < NUMBER_CITIES; v++)
        if (!visited_set[v] && distances[v] <= min) {
            min = distances[v];
            min_index = v;
        }
    return min_index;
}

void dijkstra_matrix(const unsigned short graph[NUMBER_CITIES][NUMBER_CITIES],
                     unsigned short src, unsigned short dest,
                     struct RoadMap *roadMap) {
    short distances[NUMBER_CITIES];
    bool visited_set[NUMBER_CITIES];
    short path[NUMBER_CITIES]; // used to store the path sequence

    // initialize the distances to the nodes at infinity and the path at all -1
    for (int i = 0; i < NUMBER_CITIES; i++) {
        distances[i] = SHRT_MAX;
        visited_set[i] = false;
        path[i] = -1;
    }

    distances[src] = 0;

    for (int count = 0; count < NUMBER_CITIES - 1; count++) {
        short u = min_distance(distances, visited_set);
        if (u == dest) {
            break; // stop if the destination is reached
        }
        visited_set[u] = true;

        for (int v = 0; v < NUMBER_CITIES; v++) {
            if (!visited_set[v] && graph[u][v] && distances[u] != SHRT_MAX &&
                distances[u] + graph[u][v] < distances[v]) {
                distances[v] = distances[u] + graph[u][v];
                path[v] = u;
            }
        }
    }

    // construct the path from src to dest using the path array
    short stack[NUMBER_CITIES];
    short stack_index = 0;
    short current = dest;

    while (current != -1 && current != src) {
        stack[stack_index++] = current;
        current = path[current];
    }

    if (current == src) {
        stack[stack_index++] = src;

        // reverse the stack
        for (short i = 0; i < stack_index / 2; i++) {
            short temp = stack[i];
            stack[i] = stack[stack_index - i - 1];
            stack[stack_index - i - 1] = temp;
        }

        // populate the roadMap struct given as arg
        roadMap->total_cost = 0;
        struct RoadMap *currentRoadMap = malloc(sizeof(struct RoadMap));
        roadMap = currentRoadMap;

        for (short i = 0; i < stack_index; i++) {
            currentRoadMap->city_id = stack[i];
            currentRoadMap->total_cost = distances[stack[i]];

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

void dijikstra_list(struct City **cities_list, unsigned short src,
                    unsigned short dest) {
    unsigned short distances[NUMBER_CITIES];
    bool visited_set[NUMBER_CITIES];
    short path[NUMBER_CITIES]; // used to store the path sequence

    // initialize the distances to the nodes at infinity and path at -1
    for (short i = 0; i < NUMBER_CITIES; i++) {
        distances[i] = SHRT_MAX;
        visited_set[i] = false;
        path[i] = -1;
    }

    distances[src] = 0;
}
