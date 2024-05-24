#include "queue.h"

// Definition of the global variable
struct FamilyTreeNode end_loop;

struct FamilyTreeNode *dequeue(struct queue *que) {
    end_loop.city_id = -2;
    if (que->top == NULL) {
        return &end_loop;
    }
    struct iqueue *temp = que->top;
    que->top = temp->next;
    return &(temp->value);
}

void printQueue(struct queue *que) {
    struct iqueue *current = que->top;
    printf("\nqueue: ");
    while (current != NULL) {
        printf("%d ", current->value.city_id);
        current = current->next;
    }
    printf("\n");
}

void addqueue(struct queue *que, struct FamilyTreeNode val) {
    // Allocate memory for a new node
    struct iqueue *newIqueue = (struct iqueue *)malloc(sizeof(struct iqueue));

    newIqueue->value = val;
    newIqueue->next = NULL;

    // If the queue is empty, insert the new node at the top
    if (que->top == NULL) {
        que->top = newIqueue;
    } else {
        // Traverse to the end of the queue
        struct iqueue *current = que->top;

        while (current->next != NULL) {
            current = current->next;
        }

        // Add the new node at the end of the queue
        current->next = newIqueue;
    }
}

void freequeue(struct queue *que) {
    // Pointer to keep track of the current node
    struct iqueue *current = que->top;

    // Traverse the queue and free each node
    while (current != NULL) {
        struct iqueue *temp = current; // Temporary pointer to the current node
        current = current->next;       // Move to the next node
        if(temp != NULL)
            free(temp);                    // Free the current node
        temp = NULL;
    }

    // Set the top of the queue to NULL since it's now empty
    que->top = NULL;
}
