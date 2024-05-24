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

#include "queue.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// GENERAL TREE FUNCTIONS:
void New_Nodes(struct FamilyTreeNode *prev_node);
void Free_Tree(struct FamilyTreeNode *root);
void Def_Node(struct FamilyTreeNode *node, short city_n);
void FreeTravelTree(short *arr);

// DFS FUNCTIONS:
void DFS(struct FamilyTreeNode *root);
void Print_Tree_DFS(struct FamilyTreeNode *root);
short *Travel_Tree_DFS(struct FamilyTreeNode *root);

// BFS FUNCTIONS:
void BFS(struct FamilyTreeNode *root);
void Print_Tree_BFS(struct FamilyTreeNode *root);
void Travel_Tree_BFS(struct FamilyTreeNode *root, short *arr);

#endif // TREE_H
