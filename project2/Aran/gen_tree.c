#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h> // Temp

#include "stack.h"



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

void Print_Tree(struct FamilyTreeNode *root){
    
    struct FamilyTreeNode *currentNode = root;

    // Create an empty stack and push the root node onto it
    struct stack c_stack;
    c_stack.top = NULL;
    push(&c_stack, *root);

    // Loop while the stack is not empty
    while (c_stack.top != NULL)
    {
        // Pop a node from the stack
        currentNode = pop(&c_stack);

        // Print data
        printf("\nCity: %d. Couple: %s and %s.\n", currentNode->city_id, currentNode->motherName, currentNode->fatherName);        

        // Push the children of the current node onto the stack
        // Push right child first so the left child is processed first (if binary tree)
        if (currentNode->father_parents != NULL)
            push(&c_stack, *(currentNode->father_parents));
        
        if (currentNode->mother_parents != NULL)
            push(&c_stack, *(currentNode->mother_parents));

    }
}

//--------------------------------
// DFS:
//--------------------------------
void DFS(struct FamilyTreeNode *root){
    printf("\nStarting DFS... ");
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
    printf("Done\n");
}



// BFS:





int main(){
    struct FamilyTreeNode root;
    Def_Node(&root, 0);
    New_Nodes(&root);
    DFS(&root);
    Print_Tree(&root);
    return 0;
}