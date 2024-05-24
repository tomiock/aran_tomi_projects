#include "stack.h"

// Definition of the global variable
struct FamilyTreeNode end_loop;

struct FamilyTreeNode *pop(struct stack *stk) {
    if (stk->top == NULL) {
        end_loop.city_id = -2;
        return &end_loop;
    }

    struct istack *temp = stk->top;
    struct FamilyTreeNode *popValue;
    
    popValue = (stk->top->value);
    stk->top = temp->next;
    if(temp != NULL)
        free(temp);
    temp = NULL;

    //printf("Popped node: %p, Stack top is now: %p\n", (void *)popValue, (void *)stk->top);

    return popValue;
}

void printStack(struct stack *stk) {
    struct istack *current = stk->top;
    printf("Stack: ");
    while (current != NULL) {
        printf("%d ", current->value->city_id);
        current = current->next;
    }
    printf("\n");
}

void push(struct stack *stk, struct FamilyTreeNode *val) {
    // TODO: check
    struct istack *newIstack = (struct istack *)malloc(sizeof(struct istack));
    if (newIstack == NULL) {
        perror("Failed to allocate memory for newIstack");
        exit(EXIT_FAILURE);
    }
    newIstack->value = val;
    newIstack->next = stk->top;
    stk->top = newIstack;

    //printf("Pushed node: %p, Stack top is now: %p\n", (void *)newIstack, (void *)stk->top);

}

void freeStack(struct stack *stk) {
    while (stk->top != NULL) {
        struct istack *temp = stk->top;
        stk->top = stk->top->next;
        if(temp != NULL)
            free(temp);
        temp = NULL;
    }
}