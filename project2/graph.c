#include <stdio.h>
#include <stdlib.h>

#include "graph.h"
#include "small.h"

void print_adjacency_matrix(int matrix[NUMBER_CITIES][NUMBER_CITIES]) {
  for (int i = 0; i < NUMBER_CITIES; i++) {
    for (int j = 0; j < NUMBER_CITIES; j++) {
      printf("%4d ", matrix[i][j]);
    }
    printf("\n");
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
  // make sure to free all the memory of the dynamically allocated struct cities and neighbors
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
