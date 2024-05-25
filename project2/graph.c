#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

void print_adjacency_matrix(int matrix[NUMBER_CITIES][NUMBER_CITIES]) {
    for (int i = 0; i < NUMBER_CITIES; i++) {
        for (int j = 0; j < NUMBER_CITIES; j++) {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void printRoadMap(struct RoadMap *roadMap) {
    struct RoadMap *current = roadMap;
    short cumulative_cost = 0;

    while (current != NULL) {
        printf("%s", citiesInfo[current->city_id].city_name);
        cumulative_cost = current->total_cost;

        // if it is the last element, we do not add the -
        if (current->next != NULL) {
            printf("-");
        }
        current = current->next;
    }
    printf(" %d\n", cumulative_cost);
}

// there is a difference between printing the total road map and the partial
// road map therefore we made two different functions
void printTOTALRoadMap(struct RoadMap *roadMap) {
    struct RoadMap *current = roadMap;
    short cumulative_cost = 0;

    while (current != NULL) {
        printf("%s", citiesInfo[current->city_id].city_name);
        cumulative_cost = current->total_cost;

        if (current->next != NULL) {
            printf("-");
        }
        current = current->next;
    }
    printf("\n\nTotal cost: %d\n", cumulative_cost);
}

void addRoadMap(struct RoadMap *roadMap, int city_id, int total_cost) {
    struct RoadMap *current = roadMap;
    while (current != NULL) {
        current = current->next;
    }
    current->city_id = city_id;
    current->total_cost = total_cost + current->total_cost;
    current->next = NULL;
}

// since when forming the global road trip we are joining several road maps
// we can use this function to redefine the last element to point to the first
// element of another road map
void appendRoadMap(struct RoadMap *roadMap, struct RoadMap *newRoadMap) {
    struct RoadMap *current = roadMap;

    if (current == NULL || newRoadMap == NULL) {
        return;
    }
    
    while (current->next != NULL) {
        current = current->next;
    }

    int cumulative_cost = current->total_cost;

    // we need to skip the first element of the newRoadMap since it would be
    // repeated

    newRoadMap = newRoadMap->next;
    current->next = newRoadMap;

    // another loop to add the total cost of the first map to the second, since
    // we want to express the cumulative cost of the whole path at each of its
    // elements
    while (newRoadMap != NULL) { // Here
        newRoadMap->total_cost += cumulative_cost;
        newRoadMap = newRoadMap->next;
    }
}

void freeRoadMap(struct RoadMap *roadMap) {
    struct RoadMap *current = roadMap;
    struct RoadMap *next;

    while (current != NULL) {
        next = current->next;
        if(current!=NULL)
            free(current);
        current = next;
    }
}

// since the adjency matrix is both sparce and symmetric, it is more space
// efficient to stored it in a list of the cities. each node in the list
// contains the number of neighbors of the city and an array of the neighbors
void matrix_to_list(int matrix[NUMBER_CITIES][NUMBER_CITIES],
                    struct City *cities[NUMBER_CITIES]) {
    for (int i = 0; i < NUMBER_CITIES; i++) {
        unsigned int count = 0;

        for (int j = 0; j < NUMBER_CITIES; j++) {
            if (matrix[i][j] != 0) {
                count++;
            }
        }

        if (cities[i] == NULL) {
            cities[i] = malloc(sizeof(struct City));
        }

        cities[i]->id = i;
        cities[i]->num_neighbors = count;
        cities[i]->neighbors = malloc(count * sizeof(struct Neighbor *));

        unsigned int index = 0;

        for (int j = 0; j < NUMBER_CITIES; j++) {
            if (matrix[i][j] != 0) {
                struct Neighbor *neighbor = malloc(sizeof(struct Neighbor));
                neighbor->id = j;
                neighbor->distance = matrix[i][j];

                cities[i]->neighbors[index++] = neighbor;
            }
        }
    }
}

// make sure to free all the memory of the dynamically allocated struct cities
// and neighbors
void free_cities_list(struct City *cities[NUMBER_CITIES]) {
    for (int i = 0; i < NUMBER_CITIES; i++) {
        if (cities[i] != NULL) {

            for (unsigned int j = 0; j < cities[i]->num_neighbors; j++) {
                if(cities[i]->neighbors[j] != NULL)
                    free(cities[i]->neighbors[j]);
                cities[i]->neighbors[j] = NULL;
            }

            if(cities[i]->neighbors != NULL)
                free(cities[i]->neighbors);
            cities[i]->neighbors = NULL;
            if(cities[i] != NULL)
                free(cities[i]);
            cities[i] = NULL;
        }
    }
}
