#ifdef DATASET_SMALL
#include "datasets/small.h"
#elif defined(DATASET_MEDIUM)
#include "datasets/medium.h"
#elif defined(DATASET_LARGE)
#include "datasets/large.h"
#else
#error "No dataset size defined"
#endif

#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>

extern struct FamilyTreeNode end_loop;

struct iqueue {
    struct FamilyTreeNode value;
    struct iqueue *next;
};

struct queue {
    struct iqueue *top;
};

struct FamilyTreeNode *dequeue(struct queue *que);
void printQueue(struct queue *que);
void addqueue(struct queue *que, struct FamilyTreeNode val);

#endif // queue_H
