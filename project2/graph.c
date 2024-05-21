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

void a_star(struct City *cities[NUMBER_CITIES], void *start, void *end,
            struct RoadMap *map) {
  // init the search at id 0 : TODO figure out better strategy

  unsigned int current_node;
  // we are using pointers to detect error (NULL means error)
  if (start == NULL) {
    current_node = 0;
    start = &current_node;
  } else {
    current_node = *((unsigned int *)start);
  }

  if (end == NULL) {
    printf(
        "End node is NULL. Provide a valid value (pointer to unsigned int).");
    exit(1);
  }

  // early exit
  if (current_node == *((unsigned int *)end)) {
    map->next = NULL;
    map->city_id = current_node;
    // a map with total cost 0 means that the start and goal nodes are the same
    // one
    map->total_cost = 0;

    return;
  }

  // we need a set of discovered nodes, we use a linked list
  // define open node set
  struct NodeOpenSet *open_set;
  open_set = malloc(sizeof(struct NodeOpenSet));
  open_set->city = cities[current_node];
  open_set->next = NULL;
  open_set->prev = NULL; // only node in the linked list
}
