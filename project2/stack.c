#include "stack.h"

// Definition of the global variable
struct FamilyTreeNode end_loop;

struct FamilyTreeNode *pop(struct stack *stk) {
    if (stk->top == NULL) {
        end_loop.city_id = -2;
        return &end_loop;
    }

    struct istack *temp = stk->top;
    struct FamilyTreeNode *popValue = (struct FamilyTreeNode *)malloc(sizeof(struct FamilyTreeNode));
    if (popValue == NULL) {
        perror("Failed to allocate memory for popValue");
        exit(EXIT_FAILURE);
    }
    
    *popValue = stk->top->value;
    stk->top = temp->next;
    free(temp);
    return popValue;
}

void printStack(struct stack *stk) {
    struct istack *current = stk->top;
    printf("Stack: ");
    while (current != NULL) {
        printf("%d ", current->value.city_id);
        current = current->next;
    }
    printf("\n");
}

void push(struct stack *stk, struct FamilyTreeNode val) {
    // TODO: check
    struct istack *newIstack = (struct istack *)malloc(sizeof(struct istack));
    if (newIstack == NULL) {
        perror("Failed to allocate memory for newIstack");
        exit(EXIT_FAILURE);
    }
    newIstack->value = val;
    newIstack->next = stk->top;
    stk->top = newIstack;
}

void freeStack(struct stack *stk) {
    while (stk->top != NULL) {
        struct istack *temp = stk->top;
        stk->top = stk->top->next;
        free(temp);
    }
}