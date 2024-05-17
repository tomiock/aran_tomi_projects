#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdio.h>
#include "small.h"

extern struct FamilyTreeNode end_loop;

struct istack {
    struct FamilyTreeNode value;
    struct istack* next;
};

struct stack {
    struct istack* top;
};

struct FamilyTreeNode* pop(struct stack* stk);
void printStack(struct stack* stk);
void push(struct stack* stk, struct FamilyTreeNode val);

#endif // STACK_H