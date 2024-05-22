#include "stack.h"

// Definition of the global variable
struct FamilyTreeNode end_loop;

struct FamilyTreeNode *pop(struct stack *stk) {
    end_loop.city_id = -2;
    if (stk->top == NULL) {
        return &end_loop;
    }
    struct istack *temp = stk->top;
    // TODO: check
    struct FamilyTreeNode *popValue = (struct FamilyTreeNode *)malloc(
        sizeof(struct FamilyTreeNode)); // check if dynamically needed here
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
    struct istack *newIstack = (struct istack *)malloc(
        sizeof(struct istack)); // check if dynamically needed here
    newIstack->value = val;
    newIstack->next = stk->top;
    stk->top = newIstack;
}
