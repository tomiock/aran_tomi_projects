#include <stdio.h>
#include <stdlib.h>

struct CivilRegistry
{
    int city_id;
    char city_name[20];
    char mother_name[10];
    char father_name[10];
    int mother_parents_city_id;
    int father_parents_city_id;
};


typedef struct TreeNode{
    char mother_name[10];
    char father_name[10];
    int city_id;
    struct TreeNode *mother_parents;
    struct TreeNode *father_parents;
}TreeNode;

// DFS:



// BFS:


int main(){
    return 0;
}