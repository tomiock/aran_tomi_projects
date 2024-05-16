#include <stdio.h>

#include "graph.h"

void print_adjacency_matrix(int matrix[NUMBER_CITIES][NUMBER_CITIES]) {
    for (int i = 0; i < NUMBER_CITIES; i++) {
        for (int j = 0; j < NUMBER_CITIES; j++) {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
}
