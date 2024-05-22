#include <stdio.h>
#include <stdlib.h>

#include "datasets/small.h"
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
  int total_cost;

  while (current != NULL) {
    printf("%s", citiesInfo[current->city_id].city_name);
    if (current->next != NULL) {
      printf("-");
    }
    total_cost = current->total_cost;
    current = current->next;
  }
  printf(" %d\n", total_cost);
}

void printTOTALRoadMap(struct RoadMap *roadMap) {
  struct RoadMap *current = roadMap;
  int cumulative_cost;

  while (current != NULL) {
    printf("%s", citiesInfo[current->city_id].city_name);
    if (current->next != NULL) {
      printf("-");
    }
    cumulative_cost = current->total_cost;
    current = current->next;
  }
  printf("\n");
  printf("Total cost: %d\n", cumulative_cost);
}

void addRoadMap(struct RoadMap *roadMap, int city_id, int total_cost) {
  struct RoadMap *current = roadMap;
  while (current != NULL) {
    current = current->next;
  }
  current = malloc(sizeof(struct RoadMap));
  current->city_id = city_id;
  current->total_cost = total_cost + current->total_cost;
  current->next = NULL;
}

void appendRoadMap(struct RoadMap *roadMap, struct RoadMap *newRoadMap) {
  struct RoadMap *current = roadMap;

  while (current->next != NULL) {
    current = current->next;
  }
  int cumulative_cost = current->total_cost;

  // we need to skip the first element of the newRoadMap since it would be repeated
  current->next = newRoadMap->next;

  // another loop to add the total cost of the first map to the second, since we want to express
  // the cumulative cost of the whole path at each of its elements
  while (newRoadMap != NULL) {
    newRoadMap->total_cost += cumulative_cost;
    newRoadMap = newRoadMap->next;
  }
}

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

void free_cities_list(struct City *cities[NUMBER_CITIES]) {
  // make sure to free all the memory of the dynamically allocated struct cities
  // and neighbors
  for (int i = 0; i < NUMBER_CITIES; i++) {
    if (cities[i] != NULL) {

      for (unsigned int j = 0; j < cities[i]->num_neighbors; j++) {
        free(cities[i]->neighbors[j]);
      }

      free(cities[i]->neighbors);
      free(cities[i]);
    }
  }
}
