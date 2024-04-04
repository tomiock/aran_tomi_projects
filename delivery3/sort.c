// Degree: AI
// Subject: FP2
// Delivery: 3
// Main program 
// This file also contains functions for: 
// - measuring time
// - checking input arguments 
// - initialize, print and release array to work with

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "bubble.h"
#include "merge.h"

enum sortType {bubbleType=0, mergeType=1};

// Set of functions for measuring time
double cp_Wtime_sec_micro()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + 1.0e-6 * tv.tv_usec;
}

long int cp_Wtime_micro()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec*1000000 + tv.tv_usec;
}

long int cp_Wtime_sec()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec;
}

// Function to check input arguments
void checkArguments(int argc, char ** argv)
{
    if (argc != 3)
    {
        printf ("Error...\n");
        printf ("Format: program sortType size\n");
        printf ("sortType: 0 or 1 (0 bubble sort, 1 merge sort)\n");
        printf ("size: number of elements you want to sort (integer)\n");
        exit(-1);
    }
    if (argc == 3 && (atoi(argv[1]) != 0 && atoi(argv[1]) != 1))
    {
        printf ("Error in sorting type \n");
        exit(-1);
    }
    if (argc == 3 && (atoi(argv[2]) <= 0))
    {
        printf ("Error in the number of elements to sort. It must be positive.\n");
        exit(-1);
    }
}

// Function to initialize an array with random values
int * initArray(int size)
{
    int * array=malloc(sizeof(int)*size);
    for (int i = 0; i < size; i++)
        array[i]=rand()%(2*size);
    return array;
}

// Function to release an array
void freeArray(int * array)
{
    free (array);
}

// Function to print an array
void printArray(int * array, enum sortType type, int size)
{
    int i;
    if (type==0)
        printf("Sorted array using bubble sort: \n");
    else if (type==1)    
        printf("Sorted array using merge sort: \n");
    else // -1 print array before sorting
        printf("Array before sorting: \n");
    for (i = 0; i < size; i++)
        printf("%d ", array[i]);
    printf("\n");
}
 
// main program 
int main(int argc, char ** argv)
{
    checkArguments(argc, argv);
    enum sortType type=atoi(argv[1]);
    int size=atoi(argv[2]);
    int * array = initArray(size);
    printArray(array, -1, size);
    long int first_time = cp_Wtime_micro();
    if (type==0)
        bubbleSort(array, size);
    else //if (type==1)
    {
        int * arrayAux=malloc(sizeof(int)*size);
        mergeSort(0, size-1, array, arrayAux);
        freeArray(arrayAux);
    }
    long int second_time = cp_Wtime_micro();
    printArray(array, type, size);
    freeArray(array);
    printf("First time: %ld and second time: %ld\n", first_time, second_time);
    printf("It has take %ld microseconds.\n", second_time-first_time);
    return 0;
}