#include <stdio.h>
#include <stdlib.h>
#include "small.h"

// DFS:



// BFS:



// GENERAL:

void New_Nodes(struct FamilyTreeNode *prev_node){
    struct FamilyTreeNode *new_fat, *new_mot;
    new_fat = malloc(sizeof(struct FamilyTreeNode));
    new_mot = malloc(sizeof(struct FamilyTreeNode));
    prev_node->father_parents = new_fat;
    prev_node->mother_parents = new_mot;
}

void Free_Tree(struct FamilyTreeNode *root){ //TODO
    struct FamilyTreeNode *current = root, *next;
    while(current!=NULL){

    }
}

void Def_Node(struct FamilyTreeNode *node, int city_n){
    node->city_id = 0;
    strcpy(node->fatherName, citiesInfo[city_n].father_name);
    strcpy(node->motherName, citiesInfo[city_n].mother_name);
}

int main(){
    struct FamilyTreeNode root;
    Free_Tree(&root);
    return 0;
}