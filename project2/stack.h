#ifdef DATASET_SMALL
#include "datasets/small.h"
#elif defined(DATASET_MEDIUM)
#include "datasets/medium.h"
#elif defined(DATASET_LARGE)
#include "datasets/large.h"
#else
#error "No dataset size defined"
#endif

#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>

extern struct FamilyTreeNode end_loop;

struct istack {
    struct FamilyTreeNode value;
    struct istack *next;
    int depth;
};

struct stack {
    struct istack *top;
};

struct FamilyTreeNode *pop(struct stack *stk);
void printStack(struct stack *stk);
void push(struct stack *stk, struct FamilyTreeNode val);
void freeStack(struct stack *stk);

#endif // STACK_H
