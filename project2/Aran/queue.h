    #ifndef QUEUE_H
    #define QUEUE_H

    #include <stdlib.h>
    #include <stdio.h>
    #include "dataset.h"

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