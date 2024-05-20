## Graph Implementation:
- [ ] To not use sparse matrix (see how it is acessed and loaded in memory

> The thing is that there in the matrix form there is quite the amount of lookups that need to happen. There needs to be a loop that goes though the neighbords and checks if there is zero or not.
> That is there are two loops:
> - Loop to look for the neighbors
> - Loop to look for each neighbor
>
> If the two of them are combined maybe then the loop size is constant and depends on the matrix size.
> Use list to represent the graph and then the loops depends on the amount of neighbors, not on the matrix size.
>
> Moreover, keep in mind that the time is going to be longer for low N (matrix size), then there will be a point where the matrix size is large enough that the list storage is faster.

- [ ] Struct to represent a graph:
- [ ] Use the following to represent a travel path "el camino" struct:
```c
struct RoadMap {
    int city_id;
    int total_cost;
    struct RoadMap *next;
};
```
- [ ] `addToRoadMap()` method to add a new road to the graph
- [ ] `printRoadMap()` method to print the road map
- [ ] `deleteAllRoadMap()` method to delete all the roads in the graph
- [ ] A-star Implementation

## Family Tree Implementation
- [x] TreeStruct:
```c
struct FamilyTreeNode
{
    char mother_name[10];
    char father_name[10];
    int city_id;
    struct FamilyTreeNode * mother_parents;
    struct FamilyTreeNode * father_parents;
}
```
