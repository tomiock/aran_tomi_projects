## Graph Implementation:
- [ ] Uses adjacency matrix as the state representation
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
