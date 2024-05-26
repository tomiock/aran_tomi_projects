#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

// Define constants
#define NUMBER_CITIES 10       
#define MAX_NAME 10
#define MAX_CITY_NAME 20

typedef struct CivilRegistry {
    int city_id;
    char city_name[MAX_CITY_NAME];
    char mother_name[MAX_NAME];
    char father_name[MAX_NAME];
    int mother_parents_city_id;
    int father_parents_city_id;
} CivilRegistry;

typedef struct RoadMap {
    int city_id;
    int total_cost;
    struct RoadMap *next;
} RoadMap;

typedef struct FamilyTreeNode {
    char motherName[MAX_NAME];
    char fatherName[MAX_NAME];
    int city_id;
    struct FamilyTreeNode *mother_parents;
    struct FamilyTreeNode *father_parents;
} FamilyTreeNode;

struct FamilyTreeNode* createNode(char mother_name[], char father_name[], int city_id) {
    struct FamilyTreeNode* newNode = (struct FamilyTreeNode*)malloc(sizeof(struct FamilyTreeNode));
    strcpy(newNode->motherName, mother_name);
    strcpy(newNode->fatherName, father_name);
    newNode->city_id = city_id;
    newNode->mother_parents = NULL;
    newNode->father_parents = NULL;
    return newNode;
}

struct FamilyTreeNode* createFamilyTreeNodeFromRegistry(struct CivilRegistry registry[], int city_id) {
    if (city_id == -1 || city_id >= NUMBER_CITIES)
        return NULL;
    struct CivilRegistry *city = &registry[city_id];
    struct FamilyTreeNode *node = createNode(city->mother_name, city->father_name, city_id);
    node->mother_parents = createFamilyTreeNodeFromRegistry(registry, city->mother_parents_city_id);
    node->father_parents = createFamilyTreeNodeFromRegistry(registry, city->father_parents_city_id);
    return node;
}

typedef struct QueueNode {
    int city_id;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue {
    QueueNode *front;
    QueueNode *rear;
} Queue;

struct CivilRegistry citiesInfo[NUMBER_CITIES];
struct RoadMap *roadmap = NULL;
struct RoadMap *completeRoute = NULL;

// Queue functions
Queue* createQueue();
void enqueue(Queue *queue, int city_id);
int dequeue(Queue *queue);
bool isQueueEmpty(Queue *queue);
void freeQueue(Queue *queue);

// Function implementations
void addToRoadMap(RoadMap **roadmap, int city_id, int total_cost) {
    RoadMap *new_city = (RoadMap *)malloc(sizeof(RoadMap));
    new_city->city_id = city_id;
    new_city->total_cost = total_cost;
    new_city->next = NULL;

    if (*roadmap == NULL) {
        *roadmap = new_city;
    } else {
        RoadMap *current = *roadmap;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_city;
    }
}

void printRoadMap(RoadMap *roadmap) {
    RoadMap *current = roadmap;
    while (current != NULL) {
        printf("%s", citiesInfo[current->city_id].city_name);
        if (current->next != NULL) {
            printf("-");
        }
        current = current->next;
    }
}

void appendRoadMapToCompleteRoute(RoadMap **completeRoute, RoadMap *roadmap) {
    RoadMap *current = roadmap;
    while (current != NULL) {
        // Verificar si la ciudad ya está presente en la ruta completa
        if (*completeRoute == NULL || (*completeRoute)->city_id != current->city_id) {
            addToRoadMap(completeRoute, current->city_id, current->total_cost);
        }
        current = current->next;
    }
}


void freeRoadMap(RoadMap *roadmap) {
    RoadMap *current = roadmap;
    while (current != NULL) {
        RoadMap *temp = current;
        current = current->next;
        free(temp);
    }
}

int findMinDistance(int distances[], bool visited[]) {
    int min = INT_MAX;
    int minIndex = -1;

    for (int i = 0; i < NUMBER_CITIES; i++) {
        if (!visited[i] && distances[i] <= min) {
            min = distances[i];
            minIndex = i;
        }
    }

    return minIndex;
}

void reverseRoadMap(RoadMap **roadmap) {
    RoadMap *prev = NULL;
    RoadMap *current = *roadmap;
    RoadMap *next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    *roadmap = prev;
}

int RouteSearch(int source, int destination, int adjacency_matrix[NUMBER_CITIES][NUMBER_CITIES]) {
    int distances[NUMBER_CITIES];
    bool visited[NUMBER_CITIES];
    int previous[NUMBER_CITIES];

    for (int i = 0; i < NUMBER_CITIES; i++) {
        distances[i] = INT_MAX;
        visited[i] = false;
        previous[i] = -1;
    }

    distances[source] = 0;

    for (int count = 0; count < NUMBER_CITIES - 1; count++) {
        int u = findMinDistance(distances, visited);
        if (u == -1) break;  // If no more cities are reachable, break

        visited[u] = true;

        for (int v = 0; v < NUMBER_CITIES; v++) {
            if (!visited[v] && adjacency_matrix[u][v] && distances[u] != INT_MAX &&
                distances[u] + adjacency_matrix[u][v] < distances[v]) {
                distances[v] = distances[u] + adjacency_matrix[u][v];
                previous[v] = u;
            }
        }
    }

    if (distances[destination] == INT_MAX) {
        printf("No path found from city %s to city %s.\n", citiesInfo[source].city_name, citiesInfo[destination].city_name);
        return -1;
    }

    int total_cost = distances[destination];

    // Construct the path
    RoadMap *tempRoadMap = NULL;
    int temp = destination;
    while (temp != -1) {
        addToRoadMap(&tempRoadMap, temp, distances[temp]);
        temp = previous[temp];
    }

    // Reverse the tempRoadMap to correct the order
    reverseRoadMap(&tempRoadMap);

    // Append the reversed tempRoadMap to the main roadmap
    appendRoadMapToCompleteRoute(&roadmap, tempRoadMap);

    // Free the temporary road map
    freeRoadMap(tempRoadMap);

    return total_cost;
}

// Queue functions
Queue* createQueue() {
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

void enqueue(Queue *queue, int city_id) {
    QueueNode *new_node = (QueueNode *)malloc(sizeof(QueueNode));
    new_node->city_id = city_id;
    new_node->next = NULL;
    if (queue->rear == NULL) {
        queue->front = queue->rear = new_node;
        return;
    }
    queue->rear->next = new_node;
    queue->rear = new_node;
}

int dequeue(Queue *queue) {
    if (queue->front == NULL) {
        return -1;
    }
    QueueNode *temp = queue->front;
    int city_id = temp->city_id;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    return city_id;
}

bool isQueueEmpty(Queue *queue) {
    return queue->front == NULL;
}

void freeQueue(Queue *queue) {
    while (!isQueueEmpty(queue)) {
        dequeue(queue);
    }
    free(queue);
}

void DFS(struct FamilyTreeNode* node, int flecha, Queue* cityQueue) {
    if (node == NULL) {
        return;
    }
    for (int i = 0; i < flecha; i++) {
        printf("->");
    }
    printf("%s and %s (%s)\n", node->motherName, node->fatherName, citiesInfo[node->city_id].city_name);

    // Enqueue the city ID for route calculations
    enqueue(cityQueue, node->city_id);

    DFS(node->mother_parents, flecha + 1, cityQueue);
    DFS(node->father_parents, flecha + 1, cityQueue);
}
void BFS(FamilyTreeNode* root, Queue* cityQueue) {
    if (root == NULL) return;

    Queue *nodeQueue = createQueue();
    Queue *levelQueue = createQueue(); // To track levels for printing arrows
    enqueue(nodeQueue, root->city_id);
    enqueue(levelQueue, 0); // Root level

    while (!isQueueEmpty(nodeQueue)) {
        int current_city_id = dequeue(nodeQueue);
        int current_level = dequeue(levelQueue);
        FamilyTreeNode *current = createFamilyTreeNodeFromRegistry(citiesInfo, current_city_id);

        for (int i = 0; i < current_level; i++) {
            printf("->");
        }
        printf("%s and %s (%s)\n", current->motherName, current->fatherName, citiesInfo[current_city_id].city_name);

        // Enqueue the city ID for route calculations
        enqueue(cityQueue, current_city_id);

        // No need to enqueue children here
        // Children are already created when the node is created

        if (current->mother_parents != NULL) {
            enqueue(nodeQueue, current->mother_parents->city_id);
            enqueue(levelQueue, current_level + 1);
        }
        
        if (current->father_parents != NULL) {
            enqueue(nodeQueue, current->father_parents->city_id);
            enqueue(levelQueue, current_level + 1);
        }
    }

    freeQueue(nodeQueue);
    freeQueue(levelQueue);
}

int main() {
    // Define the adjacency matrix and city information
    int adjacency_matrix[NUMBER_CITIES][NUMBER_CITIES] = {
        {0, 100, 50, 0, 0, 0, 0, 0, 0, 0},
        {100, 0, 0, 120, 0, 0, 0, 0, 0, 0},
        {50, 0, 0, 130, 110, 0, 0, 0, 0, 0},
        {0, 120, 130, 0, 0, 0, 0, 0, 80, 0},
        {0, 0, 110, 0, 0, 70, 80, 0, 0, 0},
        {0, 0, 0, 0, 70, 0, 0, 40, 0, 0},
        {0, 0, 0, 0, 80, 0, 0, 50, 0, 0},
        {0, 0, 0, 0, 0, 40, 50, 0, 30, 100},
        {0, 0, 0, 80, 0, 0, 0, 30, 0, 90},
        {0, 0, 0, 0, 0, 0, 0, 100, 90, 0}
    };

    CivilRegistry tempCitiesInfo[NUMBER_CITIES] = {
        {0, "Barcelona", "Maria", "Jordi", 3, 5},
        {1, "Lisbon", "Madalena", "Lourenço", -1, -1},
        {2, "Madrid", "", "", -1, -1},
        {3, "Paris", "Louise", "Paul", 9, 4},
        {4, "Rome", "Agnese", "Leonardo", -1, -1},
        {5, "Zurich", "Eva", "Albert", 1, 6},
        {6, "Amsterdam", "Amber", "Finn", -1, -1},
        {7, "Vienna", "", "", -1, -1},
        {8, "Berlin", "", "", -1, -1},
        {9, "Varsovia", "Anna", "Kazimierz", -1, -1}
    };

    // Initialize citiesInfo
    for (int i = 0; i < NUMBER_CITIES; i++) {
        citiesInfo[i] = tempCitiesInfo[i];
    }

    // Create the family tree
    struct FamilyTreeNode* familyTree = createFamilyTreeNodeFromRegistry(citiesInfo, 0);

    // Create and initialize the queue
    Queue *cityQueue = createQueue();
    printf("Ancestors tree:\n");
    printf("BFS -> Names:\n\n");

    // Perform BFS to fill the queue with cities in order
    BFS(familyTree, cityQueue);

    int total_cost = 0;
    int cost;

    printf("Partial road map:\n");

    // Process the queue for BFS
    int source = dequeue(cityQueue);
    while (!isQueueEmpty(cityQueue)) {
        int destination = dequeue(cityQueue);
        cost = RouteSearch(source, destination, adjacency_matrix);
        if (cost != -1) {
            total_cost += cost;
            printRoadMap(roadmap);
            printf(" %d\n", cost);
            appendRoadMapToCompleteRoute(&completeRoute, roadmap);
        }
        freeRoadMap(roadmap);
        roadmap = NULL;
        source = destination; // Set new source for the next route search
    }

    // Print the complete route for BFS
    printf("\nTotal Road Map:\n");
    printRoadMap(completeRoute);
    printf("\nTotal cost: %d\n", total_cost);

    // Free the complete route for BFS
    freeRoadMap(completeRoute);
    completeRoute = NULL; // Reset for DFS
    freeQueue(cityQueue);

    printf("----------------------------\n");

    // Perform DFS traversal and route calculation
    printf("DFS -> Names:\n");
    Queue *dfsCityQueue = createQueue();
    DFS(familyTree, 0, dfsCityQueue);
    printf("\nPartial road map:\n");
    total_cost = 0;
    source = dequeue(dfsCityQueue);
    while (!isQueueEmpty(dfsCityQueue)) {
        int destination = dequeue(dfsCityQueue);
        cost = RouteSearch(source, destination, adjacency_matrix);
        if (cost != -1) {
            total_cost += cost;
            printRoadMap(roadmap);
            printf(" %d\n", cost);
            appendRoadMapToCompleteRoute(&completeRoute, roadmap);
        }
        freeRoadMap(roadmap);
        roadmap = NULL;
        source = destination; // Set new source for the next route search
    }

    // Print the complete route for DFS
    printf("\nTotal Road Map:\n");
    printRoadMap(completeRoute);
    printf("\nTotal cost: %d\n", total_cost);

    // Free the complete route for DFS
    freeRoadMap(completeRoute);
    freeQueue(dfsCityQueue);

    return 0;
}
