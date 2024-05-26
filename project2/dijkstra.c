#include "dijkstra.h"

struct MinHeapNode {
    int vertex;
    int distance;
} MinHeapNode;

struct MinHeap {
    int size;
    int capacity;
    int *pos;
    struct MinHeapNode **array;
};

// Function to create a new MinHeap node
struct MinHeapNode *new_MinHeapNode(int vertex, int distance) {
    struct MinHeapNode *new_min_heap_node = malloc(sizeof(struct MinHeapNode));
    new_min_heap_node->vertex = vertex;
    new_min_heap_node->distance = distance;
    return new_min_heap_node;
}

// Function to create a MinHeap
struct MinHeap *init_MinHeap(int capacity) {
    struct MinHeap *min_heap = malloc(sizeof(struct MinHeap));
    min_heap->pos = (int *)malloc(capacity * sizeof(int));
    min_heap->size = 0;
    min_heap->capacity = capacity;
    min_heap->array = malloc(capacity * sizeof(struct MinHeapNode *));
    return min_heap;
}

// Function to swap two nodes of min heap
void swapMinHeapNode(struct MinHeapNode **a, struct MinHeapNode **b) {
    struct MinHeapNode *t = *a;
    *a = *b;
    *b = t;
}

// Heapify at given index
void heapify(struct MinHeap *min_heap, int idx) {
    int smallest, left, right;
    smallest = idx; // parent
    left = 2 * idx + 1; // left child
    right = 2 * idx + 2; // right child

    if (left < min_heap->size && // check if the left child is smaller than dad
        min_heap->array[left]->distance <  // check if the distance of the left child larger
        min_heap->array[smallest]->distance) { // than the distance of the dad
            smallest = left; // if so, the left child is the smallest and we should update the smallest value
    }

    if (right < min_heap->size && // check if the right child is smaller than dad
        min_heap->array[right]->distance < min_heap->array[smallest]->distance) // check if the distance of the right child larger
        smallest = right; // update the smallest value

    if (smallest != idx) { // if this case is meet, we should swap the nodes
        struct MinHeapNode *smallestNode = min_heap->array[smallest];
        struct MinHeapNode *idxNode = min_heap->array[idx];

        min_heap->pos[smallestNode->vertex] = idx;
        min_heap->pos[idxNode->vertex] = smallest;

        swapMinHeapNode(&min_heap->array[smallest], &min_heap->array[idx]);

        // the only recursive function in our project
        heapify(min_heap, smallest);
    }
    // in case the heap property is maintained, we do nothing
    // no need to swap the nodes or recursive call
}

// extract the minimum node from the heap
struct MinHeapNode *pop_heap(struct MinHeap *min_heap) {
    if (min_heap->size == 0)
        return NULL;

    struct MinHeapNode *root = min_heap->array[0];
    struct MinHeapNode *lastNode = min_heap->array[min_heap->size - 1];
    min_heap->array[0] = lastNode;

    min_heap->pos[root->vertex] = min_heap->size - 1;
    min_heap->pos[lastNode->vertex] = 0;

    --min_heap->size; // decrease the size of the heap once the node is extracted
    heapify(min_heap, 0);
    // ensure to maintain the heap property

    return root;
}

// decrease the distance value of a given vertex
void decreaseKey(struct MinHeap *min_heap, int vertex, int distance) {
    int i = min_heap->pos[vertex];
    min_heap->array[i]->distance = distance;

    // the condition int the loop checks the two adjacent nodes to ensure
    // that the proper order (minimum distance) is maintained
    
    while (i &&  // this index is used to check if the node is the root
        min_heap->array[i]->distance < // first node 
        min_heap->array[(i - 1) / 2]->distance) { // second node
            min_heap->pos[min_heap->array[i]->vertex] = (i - 1) / 2;
            min_heap->pos[min_heap->array[(i - 1) / 2]->vertex] = i;
            swapMinHeapNode(&min_heap->array[i], &min_heap->array[(i - 1) / 2]);
            // if this two nodes are not in the right order, swap them
            // this can be seem similar to the bubble sort

        i = (i - 1) / 2;
    }
}

// check if the vertex (the data in the node) is in the min heap
bool isInMinHeap(struct MinHeap *min_heap, int vertex) {
    if (min_heap->pos[vertex] < min_heap->size)
        return true;
    return false;
}

// function to implement Dijkstra's algorithm using a min-heap
void dijkstra_matrix(int graph[NUMBER_CITIES][NUMBER_CITIES],
                     unsigned short src, unsigned short dest,
                     struct RoadMap *roadMap) {
    short distances[NUMBER_CITIES];
    bool visited_set[NUMBER_CITIES];
    short path[NUMBER_CITIES]; // used to store the path sequence

    // the heap used along the algorithm
    struct MinHeap *min_heap = init_MinHeap(NUMBER_CITIES);

    // initialize distances and min heap
    for (int i = 0; i < NUMBER_CITIES; i++) {
        distances[i] = SHRT_MAX;
        visited_set[i] = false;
        path[i] = -1;
        min_heap->array[i] = new_MinHeapNode(i, distances[i]);
        min_heap->pos[i] = i;
    }

    distances[src] = 0;
    decreaseKey(min_heap, src, distances[src]);
    min_heap->size = NUMBER_CITIES;

    while (min_heap->size > 0) {
        struct MinHeapNode *minHeapNode = pop_heap(min_heap);
        int u =
            minHeapNode->vertex; // take the vertex with the minimum distance
        visited_set[u] = true;

        if (u == dest) {
            break; // stop if the destination is reached
        }

        for (int v = 0; v < NUMBER_CITIES; v++) {
            if (!visited_set[v] && graph[u][v] && distances[u] != SHRT_MAX &&
                distances[u] + graph[u][v] < distances[v]) {
                distances[v] = distances[u] + graph[u][v];
                path[v] = u;

                if (isInMinHeap(min_heap, v))
                    decreaseKey(min_heap, v, distances[v]);
            }
        }
    }

    // construct the path from src to dest using the path array
    short stack[NUMBER_CITIES];
    short stack_index = 0;
    short current = dest;

    while (current != -1 && current != src) {
        stack[stack_index++] = current;
        current = path[current];
    }

    if (current == src) {
        stack[stack_index++] = src;

        // reverse the stack
        for (short i = 0; i < stack_index / 2; i++) {
            short temp = stack[i];
            stack[i] = stack[stack_index - i - 1];
            stack[stack_index - i - 1] = temp;
        }

        // populate the roadMap struct given as arg
        roadMap->total_cost = 0;
        struct RoadMap *currentRoadMap =
            roadMap; // define a new variable to populate the struct
        currentRoadMap->next = NULL;

        for (short i = 0; i < stack_index; i++) {
            currentRoadMap->city_id = stack[i];
            currentRoadMap->total_cost = distances[stack[i]];

            if (i < stack_index - 1) {
                currentRoadMap->next =
                    (struct RoadMap *)malloc(sizeof(struct RoadMap));
                currentRoadMap = currentRoadMap->next;
                currentRoadMap->next = NULL;
            }
        }
    } else {
        printf("No path found from src to dest\n");
    }

    // Free memory

    while (min_heap->size > 0) {
        free(min_heap->array[min_heap->size - 1]);
        min_heap->size--;
    }

    free(min_heap->array);
    free(min_heap->pos);
    free(min_heap);
}

void dijikstra_list(struct City **cities_list, unsigned short src,
                    unsigned short dest) {
    unsigned short distances[NUMBER_CITIES];
    bool visited_set[NUMBER_CITIES];
    short path[NUMBER_CITIES]; // used to store the path sequence

    // initialize the distances to the nodes at infinity and path at -1
    for (short i = 0; i < NUMBER_CITIES; i++) {
        distances[i] = SHRT_MAX;
        visited_set[i] = false;
        path[i] = -1;
    }

    distances[src] = 0;
}
