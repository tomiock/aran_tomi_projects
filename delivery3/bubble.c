// Degree: AI
// Subject: FP2
// Delivery: 3
// Implementation of functions related to bubble sort functionality

#include "bubble.h"

// A function to implement bubble sort
void swap_int(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubbleSort(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++) {
        // Last i elements are already in place
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1])
                swap_int(&arr[j], &arr[j + 1]);
        }
    }
}
