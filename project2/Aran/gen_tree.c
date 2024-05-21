#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h> // Temp

#include "stack.h"
#include "queue.h"



// GENERAL:

void New_Nodes(struct FamilyTreeNode *prev_node){
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

void Free_Tree(struct FamilyTreeNode *root){ //TODO
    struct FamilyTreeNode *current = root, *next;
    while(current!=NULL){

    }
}

void Def_Node(struct FamilyTreeNode *node, int city_n){
    node->city_id = city_n;
    strcpy(node->fatherName, citiesInfo[city_n].father_name);
    strcpy(node->motherName, citiesInfo[city_n].mother_name);
}

void Print_Tree_DFS(struct FamilyTreeNode *root){
    
    struct FamilyTreeNode *currentNode = root;

    // Create an empty stack and push the root node onto it
    struct stack c_stack;
    c_stack.top = NULL;
    push(&c_stack, *root);
    c_stack.top->depth = 0;
    int arrows;

    // Loop while the stack is not empty
    while (c_stack.top != NULL)
    {
        // Pop a node from the stack
        arrows = c_stack.top->depth;
        currentNode = pop(&c_stack);

        // Print data
        for(int i = 0; i<arrows; i++)
            printf("->");
        if(arrows>0) printf(" ");
        printf("%s and %s (%s)\n", currentNode->motherName, currentNode->fatherName, citiesInfo[currentNode->city_id].city_name);        

        // Push the children of the current node onto the stack
        // Push right child first so the left child is processed first (if binary tree)
        if (currentNode->father_parents != NULL){
            push(&c_stack, *(currentNode->father_parents));
            c_stack.top->depth = arrows + 1;
        }
        if (currentNode->mother_parents != NULL){
            push(&c_stack, *(currentNode->mother_parents));
            c_stack.top->depth = arrows + 1;
        }
    }
}

void Print_Tree_BFS(struct FamilyTreeNode *root){
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
        //printQueue(c_queue);
        // Dequeue
        currentNode = dequeue(&c_queue);
        for(int i = 0; i<arrows; i++)
            printf("->");
        if(arrows>0) printf(" ");
        printf("%s and %s (%s)\n", currentNode->motherName, currentNode->fatherName, citiesInfo[currentNode->city_id].city_name);

        //printf("\nCity: %d. Couple: %s and %s.\n", currentNode->city_id, currentNode->motherName, currentNode->fatherName);        

        if (currentNode->mother_parents != NULL){
            //printf("Adding to queue: %d ", currentNode->city_id);
            //printf("MOM: %d\n", currentNode->mother_parents->city_id);
            addqueue(&c_queue, *currentNode->mother_parents);
        }
        if (currentNode->father_parents != NULL){
            //printf("Adding to queue: %d ", currentNode->city_id);
            //printf("FAT: %d\n", currentNode->father_parents->city_id);
            addqueue(&c_queue, *currentNode->father_parents);
        }
        num_items = num_items - 1;
        if (num_items == 0){
            total_num_items = total_num_items * 2;
            num_items = total_num_items;
            arrows ++;
        }
        
    }
    printf("\n");
}

//--------------------------------
// DFS:
//--------------------------------
void DFS(struct FamilyTreeNode *root){
    // Create stack
    struct stack c_stack;
    c_stack.top = NULL;

    // Create current and initialize at root
    struct FamilyTreeNode *currentNode;
    currentNode = root;
    push(&c_stack, *currentNode);

    // Condition if currentNode is not stopped by a pop action to a void stack (see stack.h)
    while (currentNode != &end_loop){
        //printf("\nHey"); // Temp print
        //sleep(1);
        //printStack(&c_stack);
        //printf("IF: %d\n", (citiesInfo[currentNode->city_id].mother_parents_city_id)); // Temp print
        if ((citiesInfo[currentNode->city_id].mother_parents_city_id) != -1){
            int city = citiesInfo[currentNode->city_id].mother_parents_city_id;
            //printf("Mum: %d\n", city); // Temp print
            currentNode = currentNode->mother_parents;
            if (currentNode != NULL) {
                Def_Node(currentNode, city);
                New_Nodes(currentNode);
                push(&c_stack, *currentNode);
            }
        } else{
            int city;
            do{
                currentNode = pop(&c_stack);
                city = citiesInfo[currentNode->city_id].father_parents_city_id;
                
                if (currentNode == &end_loop);
                    // printf("end_loop\n"); // Temp print
                else currentNode = currentNode->father_parents;

                //if (currentNode == NULL)
                //    printf("NULL\n"); // Temp print
                //else printf("NOT NULL\n"); // Temp print
                //sleep(1);
            }while(currentNode == NULL);
            //printf("currentNode->city_id: %d\n", currentNode->city_id); // Temp print
            
            //printf("Dad: %d\n", city); // Temp print
            if (currentNode != NULL) {
                Def_Node(currentNode, city);
                New_Nodes(currentNode);
                push(&c_stack, *currentNode);
            }
        }

    }
}



//--------------------------------
// BFS:
//--------------------------------
void BFS(struct FamilyTreeNode *root){

    // Create stack                                                                            
    struct stack c_stack;
    c_stack.top = NULL;

    struct FamilyTreeNode *currentNode = root;

    if (root == NULL) {
        return;
    }

    push(&c_stack, *root);

    while (c_stack.top != NULL) {
        // Pop stack
        currentNode = pop(&c_stack);

        // Create mother node
        if (currentNode->mother_parents != NULL) {
            struct FamilyTreeNode *new_mother = currentNode->mother_parents;
            Def_Node(new_mother, citiesInfo[currentNode->city_id].mother_parents_city_id);
            New_Nodes(new_mother);
            push(&c_stack, *new_mother);
        }

        // Create father node
        if (currentNode->father_parents != NULL) {
            struct FamilyTreeNode *new_father = currentNode->father_parents;
            Def_Node(new_father, citiesInfo[currentNode->city_id].father_parents_city_id);
            New_Nodes(new_father);
            push(&c_stack, *new_father);
        }
    }
}



int main(int argc, char *argv[]){
    struct FamilyTreeNode root_dfs;
    struct FamilyTreeNode root_bfs;

    printf("Ancestors’ tree:\n\n");

    // BFS
    Def_Node(&root_bfs, 0);
    New_Nodes(&root_bfs);
    BFS(&root_bfs);
    printf("BFS-> Names:\n");
    Print_Tree_BFS(&root_bfs);
    
    printf("\n----------------------------------\n");

    // DFS
    Def_Node(&root_dfs, 0);
    New_Nodes(&root_dfs);
    DFS(&root_dfs);
    printf("DFS-> Names:\n");
    Print_Tree_DFS(&root_dfs);
    return 0;
}