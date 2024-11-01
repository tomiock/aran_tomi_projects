#include "tree.h"
#include <string.h>

// GENERAL TREE FUNCTIONS:
void New_Nodes(struct FamilyTreeNode *prev_node) {
    if (prev_node == NULL) {
        fprintf(stderr, "Error: prev_node is NULL\n");
        return;
    }

    struct FamilyTreeNode *new_fat = NULL, *new_mot = NULL;

    if (citiesInfo[prev_node->city_id].mother_parents_city_id != -1)
        new_mot = malloc(sizeof(struct FamilyTreeNode));

    if (citiesInfo[prev_node->city_id].father_parents_city_id != -1)
        new_fat = malloc(sizeof(struct FamilyTreeNode));

    prev_node->father_parents = new_fat;
    prev_node->mother_parents = new_mot;
}

void Free_Tree(struct FamilyTreeNode *root) {
    if (root == NULL) {
        return;
    }

    // Create an empty stack and push the root node onto it
    struct stack c_stack;
    c_stack.top = NULL;
    push(&c_stack, root);
    struct FamilyTreeNode *currentNode;

    // Loop while the stack is not empty
    while (c_stack.top != NULL) {
        // Pop a node from the stack
        currentNode = pop(&c_stack);
        
        //printf("Freeing node: %p\n", (void *)currentNode);
        //printf("With id: %d and a name: %s\n", currentNode->city_id, currentNode->motherName);

        // Push the children of the current node onto the stack
        // Push right child first so the left child is processed first (if binary tree)
        if (currentNode->father_parents != NULL) {
            push(&c_stack, currentNode->father_parents);
        }
        if (currentNode->mother_parents != NULL) {
            push(&c_stack, currentNode->mother_parents);
        }

        // Free the current node
        if(currentNode != NULL)
            free(currentNode);
        currentNode = NULL;
    }

    // Free the stack if necessary (depends on stack implementation)
    freeStack(&c_stack);
}

// define a node with the city number and the parents names
void Def_Node(struct FamilyTreeNode *node, short city_n) {
    node->city_id = city_n;
    strcpy(node->fatherName, citiesInfo[city_n].father_name);
    strcpy(node->motherName, citiesInfo[city_n].mother_name);
}

void FreeTravelTree(short *arr){
    if(arr!=NULL)
        free(arr);
    arr = NULL;
}


// DFS FUNCTIONS:
void DFS(struct FamilyTreeNode *root) {
    // Create stack
    struct stack c_stack;
    c_stack.top = NULL;

    // Create current and initialize at root
    struct FamilyTreeNode *currentNode, *temp;
    currentNode = root;
    push(&c_stack, currentNode);

    // Condition if currentNode is not stopped by a pop action to a void stack
    while (currentNode != &end_loop) {
        if ((citiesInfo[currentNode->city_id].mother_parents_city_id) != -1) {
            short city =
                citiesInfo[currentNode->city_id].mother_parents_city_id;
            currentNode = currentNode->mother_parents;
            if (currentNode != NULL) {
                Def_Node(currentNode, city);
                New_Nodes(currentNode);
                push(&c_stack, currentNode);
            }
        } else {
            short city;
            do {
                currentNode = pop(&c_stack);
                city = citiesInfo[currentNode->city_id].father_parents_city_id;

                if (currentNode != &end_loop){
                    temp = currentNode->father_parents;
                    currentNode = temp;
                }

            } while (currentNode == NULL);

            if (currentNode != NULL) {
                Def_Node(currentNode, city);
                New_Nodes(currentNode);
                push(&c_stack, currentNode);
            }
        }
    }
    freeStack(&c_stack);
}

void Print_Tree_DFS(struct FamilyTreeNode *root) {

    struct FamilyTreeNode *currentNode = root;

    // Create an empty stack and push the root node onto it
    struct stack c_stack;
    c_stack.top = NULL;
    push(&c_stack, root);
    c_stack.top->depth = 0;
    int arrows;

    // Loop while the stack is not empty
    while (c_stack.top != NULL) {
        // Pop a node from the stack
        arrows = c_stack.top->depth;
        currentNode = pop(&c_stack);

        // Print data
        for (int i = 0; i < arrows; i++)
            printf("->");
        if (arrows > 0)
            printf(" ");
        printf("%s and %s (%s)\n", currentNode->motherName,
               currentNode->fatherName,
               citiesInfo[currentNode->city_id].city_name);

        // Push the children of the current node onto the stack
        // Push right child first so the left child is processed first (if
        // binary tree)
        if (currentNode->father_parents != NULL) {
            push(&c_stack, (currentNode->father_parents));
            c_stack.top->depth = arrows + 1;
        }
        if (currentNode->mother_parents != NULL) {
            push(&c_stack, (currentNode->mother_parents));
            c_stack.top->depth = arrows + 1;
        }
        //free(currentNode);
    }
    freeStack(&c_stack);
}

void Travel_Tree_DFS(struct FamilyTreeNode *root, short arr[NUMBER_CITIES]) {

    struct FamilyTreeNode *currentNode = root;
    int i = 0;

    // Create an empty stack and push the root node onto it
    struct stack c_stack;
    c_stack.top = NULL;
    push(&c_stack, root);
    c_stack.top->depth = 0;

    // Loop while the stack is not empty
    while (c_stack.top != NULL) {
        // Pop a node from the stack
        currentNode = pop(&c_stack);
        arr[i] = currentNode->city_id;

        // Push the children of the current node onto the stack
        // Push right child first so the left child is processed first (if
        // binary tree)
        if (currentNode->father_parents != NULL) {
            push(&c_stack, (currentNode->father_parents));
        }
        if (currentNode->mother_parents != NULL) {
            push(&c_stack, (currentNode->mother_parents));
        }
        i++;
    }
    freeStack(&c_stack);
    for (i; i < NUMBER_CITIES; i++)
        arr[i] = -1;
}


// BFS FUNCTIONS:
void BFS(struct FamilyTreeNode *root) {

    // Create stack
    struct stack c_stack;
    c_stack.top = NULL;

    struct FamilyTreeNode *currentNode = root;

    if (root == NULL) {
        return;
    }

    push(&c_stack, root);

    while (c_stack.top != NULL) {
        // Pop stack
        currentNode = pop(&c_stack);

        // Create mother node
        if (currentNode->mother_parents != NULL) {
            struct FamilyTreeNode *new_mother = currentNode->mother_parents;
            Def_Node(new_mother,
                     citiesInfo[currentNode->city_id].mother_parents_city_id);
            New_Nodes(new_mother);
            push(&c_stack, new_mother);
        }

        // Create father node
        if (currentNode->father_parents != NULL) {
            struct FamilyTreeNode *new_father = currentNode->father_parents;
            Def_Node(new_father,
                     citiesInfo[currentNode->city_id].father_parents_city_id);
            New_Nodes(new_father);
            push(&c_stack, new_father);
        }
        //free(currentNode);
    }
    freeStack(&c_stack);
}

void Print_Tree_BFS(struct FamilyTreeNode *root) {
    // Create stack
    struct queue c_queue;
    c_queue.top = NULL;

    struct FamilyTreeNode *currentNode = root;

    if (root == NULL) {
        return;
    }

    addqueue(&c_queue, *root);
    int num_items = 1, total_num_items = 1, arrows = 0;

    while (c_queue.top != NULL) {
        // printQueue(c_queue);
        //  Dequeue
        currentNode = dequeue(&c_queue);
        for (int i = 0; i < arrows; i++)
            printf("->");
        if (arrows > 0)
            printf(" ");
        printf("%s and %s (%s)\n", currentNode->motherName,
               currentNode->fatherName,
               citiesInfo[currentNode->city_id].city_name);

        // printf("\nCity: %d. Couple: %s and %s.\n", currentNode->city_id,
        // currentNode->motherName, currentNode->fatherName);

        if (currentNode->mother_parents != NULL) {
            addqueue(&c_queue, *currentNode->mother_parents);
        }
        if (currentNode->father_parents != NULL) {
            addqueue(&c_queue, *currentNode->father_parents);
        }
        num_items = num_items - 1;
        if (num_items == 0) {
            total_num_items = total_num_items * 2;
            num_items = total_num_items;
            arrows++;
        }
        if(currentNode!=NULL)
            free(currentNode);
        currentNode = NULL;
    }
    printf("\n");
    freequeue(&c_queue);
}

void Travel_Tree_BFS(struct FamilyTreeNode *root, short arr[NUMBER_CITIES]) {
    // Create stack
    struct queue c_queue;
    c_queue.top = NULL;
    int i = 0;

    struct FamilyTreeNode *currentNode = root;

    addqueue(&c_queue, *root);

    while (c_queue.top != NULL) {

        // Dequeue
        currentNode = dequeue(&c_queue);
        arr[i] = currentNode->city_id;

        if (currentNode->mother_parents != NULL) {
            addqueue(&c_queue, *currentNode->mother_parents);
        }
        if (currentNode->father_parents != NULL) {
            addqueue(&c_queue, *currentNode->father_parents);
        }
        i++;
        if(currentNode != NULL)
            free(currentNode);
        currentNode = NULL;
    }
    // check the initialization of i (maybe it should be int i = 0)
    for (i; i < NUMBER_CITIES; i++) // TODO
        arr[i] = -1;
}
