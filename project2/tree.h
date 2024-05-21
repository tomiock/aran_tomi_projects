#ifdef DATASET_SMALL
    #include "datasets/small.h"
#elif defined(DATASET_MEDIUM)
    #include "datasets/medium.h"
#elif defined(DATASET_LARGE)
    #include "datasets/large.h"
#else
    #error "No dataset size defined"
#endif

#ifndef TREE_H
#define TREE_H

#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "queue.h"

// GENERAL TREE FUNCTIONS:
void New_Nodes(struct FamilyTreeNode *prev_node);
void Free_Tree(struct FamilyTreeNode *root);
void Def_Node(struct FamilyTreeNode *node, int city_n);


// DFS FUNCTIONS:
void DFS(struct FamilyTreeNode *root);
void Print_Tree_DFS(struct FamilyTreeNode *root);
int * Travel_Tree_DFS(struct FamilyTreeNode *root);


// BFS FUNCTIONS:
void BFS(struct FamilyTreeNode *root);
void Print_Tree_BFS(struct FamilyTreeNode *root);
int * Travel_Tree_BFS(struct FamilyTreeNode *root);


#endif // TREE_H