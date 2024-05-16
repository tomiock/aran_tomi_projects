#include <stdlib.h>
#include <stdio.h>
#include "small.h"

struct FamilyTreeNode end_loop;


struct istack
{
    struct FamilyTreeNode value;
    struct istack* next;

};

struct stack
{

    struct istack* top;

};


struct FamilyTreeNode * pop(struct stack *stk)
{
    end_loop.city_id = -2;
    if (stk->top == NULL){
        //printf("STK top NULL\n"); // Temp print
        return &end_loop;
    }
    //printf("In pop return: "); // Temp print
    struct istack* temp = stk->top;
    struct FamilyTreeNode *popValue = (struct FamilyTreeNode*)malloc(sizeof(struct FamilyTreeNode));
    *popValue = stk->top->value;
    stk->top = temp->next;
    free(temp);
    //printf("%d\n", popValue->city_id); // Temp print
    return popValue;
}

void printStack(struct stack* stk) {
    struct istack* current = stk->top;
    printf("Stack: ");
    while (current != NULL) {
        printf("%d ", current->value.city_id);
        current = current->next;
    }
    printf("\n");
}

void push(struct stack *stk, struct FamilyTreeNode val)
{
    struct istack *newIstack = (struct istack *)malloc(sizeof(struct istack));
    newIstack->value = val;
    newIstack->next = stk->top;
    stk->top = newIstack;
}

