#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10

struct Element {
    int data;
    int key;
};

struct Element *hashArray[SIZE];

// return the index to the hash table
int hashCode(int key) { return key % SIZE; }

struct Element *search(int key) {
    printf("Searching for key %d... ", key);
    // get the hash
    int hashIndex = hashCode(key);
    int hashIndexOrig = hashIndex;

    // search for the key in array until found or empty
    while (hashArray[hashIndex] != NULL) {
        if (hashArray[hashIndex]->key == key) {
            printf("Element found: key=%d, value=%d\n", hashArray[hashIndex]->key,
                   hashArray[hashIndex]->data);
            return hashArray[hashIndex];
        }
        // go to next cell
        hashIndex++;
        // wrap around the table
        hashIndex %= SIZE;
        // if we've visited all the elements, just break the loop - the element is
        // not found
        if (hashIndex == hashIndexOrig)
            break;
    }
    printf("Element not found\n");
    return NULL;
}

// reserve the memory for the element and assign key/value
// calculate the hashIndex
// search for the position (hashIndex) to insert
//       if the position is ocupied, move in the table until an empty or removed cell
// insert the element to the hash table on the found position
void insert(int key, int data) {
    struct Element *item = (struct Element *)malloc(sizeof(struct Element));
    item->data = data;
    item->key = key;

    // get the hash
    int hashIndex = hashCode(key);
    int hashIndexOrig = hashIndex;

    // move in array until an empty or deleted cell
    while (hashArray[hashIndex] != NULL && hashArray[hashIndex]->key != -1) {
        // go to next cell
        hashIndex++;
        // wrap around the table
        hashIndex %= SIZE;
        // if we've visited all the elements, just break the loop - the table is
        // full and no more elements can be inserted
        if (hashIndex == hashIndexOrig)
            printf("Table is fulli, no element has been inserted.\n");
        break;
    }
    hashArray[hashIndex] = item;
}

// calculate the hashIndex
// move in the hash table to find the element to remove
//       if the key of the place is equal to the key of the element,
//           assign -1 to the element's key and value
//       if not, go to the next position
//  you can assume that the element is found
void removeElement(struct Element *element) {
    // very similar code to the search function it has the same structure
    int hashIndex = hashCode(element->key);
    int hashIndexOrig = hashIndex;

    while (hashArray[hashIndex] != NULL) {
        if (hashArray[hashIndex]->key == element->key) {
            hashArray[hashIndex]->key = -1;
            hashArray[hashIndex]->data = -1;
            printf("Element removed\n");
            return;
        }

        hashIndex++;
        hashIndex %= SIZE;

        if (hashIndex == hashIndexOrig)
            break;
    }
    printf("Element not found\n");
}

void display() {
    for (int i = 0; i < SIZE; i++) {

        if (hashArray[i] != NULL)
            printf(" (%d,%d)", hashArray[i]->key, hashArray[i]->data);
        else
            printf(" -- ");
    }
    printf("\n");
}

int main() {
    insert(0, 0);
    insert(1, 20);
    insert(2, 70);
    insert(42, 80);
    insert(4, 25);
    insert(13, 78);
    insert(37, 97);
    display();
    printf("\n");

    struct Element *item = (struct Element *)malloc(sizeof(struct Element));

    item = search(2);
    removeElement(item);
    display();
    printf("\n");

    item = search(2);
    display();
    printf("\n");

    item = search(37);
    removeElement(item);
    display();
    printf("\n");
}
