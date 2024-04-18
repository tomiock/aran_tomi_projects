#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 10

struct Element {
   int data;   
   int key;
};

struct Element * hashArray[SIZE]; 

//return the index to the hash table
int hashCode(int key) 
{
    return key % SIZE;
}

struct Element * search(int key) 
{
    printf("Searching for key %d... ", key);
    //get the hash 
    int hashIndex = hashCode(key); 
    int hashIndexOrig=hashIndex; 
	
    //search for the key in array until found or empty 
    while(hashArray[hashIndex] != NULL) 
    {
        if(hashArray[hashIndex]->key == key)
        {
            printf("Element found: key=%d, value=%d\n", hashArray[hashIndex]->key, hashArray[hashIndex]->data);
            return hashArray[hashIndex]; 
        }
        //go to next cell
        hashIndex++;
	    //wrap around the table
        hashIndex %= SIZE;
        //if we've visited all the elements, just break the loop - the element is not found
        if (hashIndex == hashIndexOrig) break;
    }        
    printf("Element not found\n");
    return NULL;        
}

//reserve the memory for the element and assign key/value 
//calculate the hashIndex
//search for the position (hashIndex) to insert
//      if the position is ocupied, move in the table until an empty or removed cell
//insert the element to the hash table on the found position
void insert(int key, int data) 
{

}

//calculate the hashIndex
//move in the hash table to find the element to remove
//      if the key of the place is equal to the key of the element, 
//          assign -1 to the element's key and value
//      if not, go to the next position
// you can assume that the element is found
void removeElement(struct Element * element) 
{

}

void display() {
    for(int i=0; i<SIZE; i++) {
	
    if(hashArray[i] != NULL)
        printf(" (%d,%d)", hashArray[i]->key, hashArray[i]->data);
    else
        printf(" -- ");
    }
    printf("\n");
}

int main() 
{
    insert(0, 0);
    insert(1, 20);
    insert(2, 70);
    insert(42, 80);
    insert(4, 25);
    insert(13, 78);
    insert(37, 97);
    display();
    
    struct Element * item = (struct Element*) malloc(sizeof(struct Element));
    
    item = search(2);        
    removeElement(item);
    display();
    
    item = search(2);
    display();

    item = search(37);
    removeElement(item);
    display();
}
