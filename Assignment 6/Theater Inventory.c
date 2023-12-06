// Giovanni Acireale, Assignment 6, 12/3/23
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 19
#define TABLESIZE 300007

// Struct definition for an item
typedef struct item {
    char name[MAXLEN + 1];
    int quantity;
    int saleprice;
} item;

// Struct definition for a linked list node
typedef struct node {
    item* iPtr;
    struct node* next;
} node;

// Struct definition for a hashtable
typedef struct hashtable {
    node** lists;
    int size;
} hashtable;

// Hash function for mapping a string to an index in the hashtable
int hashfunc(char* word, int size) {
    int len = strlen(word);
    int res = 0;
    for (int i = 0; i < len; i++) {
        res = (1151 * res + (word[i] - 'a')) % size;
    }
    return res;
}

// Function to create a new node with the given item
node* createNode(item* iPtr) {
    node* newNode = (node*)malloc(sizeof(node));
    if (newNode == NULL) {
        perror("Error creating node");
        exit(EXIT_FAILURE);
    }

    newNode->iPtr = iPtr;
    newNode->next = NULL;

    return newNode;
}

// Function to create a new item with the given details
item* createItem(const char* name, int quantity, int saleprice) {
    item* newItem = (item*)malloc(sizeof(item));
    if (newItem == NULL) {
        perror("Error creating item");
        exit(EXIT_FAILURE);
    }

    strncpy(newItem->name, name, MAXLEN);
    newItem->quantity = quantity;
    newItem->saleprice = saleprice;

    return newItem;
}

// Function to create a new hashtable with the given size
hashtable* createHashTable(int size) {
    hashtable* hashTable = (hashtable*)malloc(sizeof(hashtable));
    if (hashTable == NULL) {
        perror("Error creating hash table");
        exit(EXIT_FAILURE);
    }

    hashTable->size = size;

    // Allocate memory for the array of linked lists
    hashTable->lists = (node**)malloc(sizeof(node*) * size);
    if (hashTable->lists == NULL) {
        perror("Error creating hash table array");
        exit(EXIT_FAILURE);
    }

    // Initialize each bucket to NULL
    for (int i = 0; i < size; ++i) {
        hashTable->lists[i] = NULL;
    }

    return hashTable;
}

// Function to insert an item into the hashtable
void insert(hashtable* hashTable, item* iPtr) {
    int index = hashfunc(iPtr->name, hashTable->size);
    node* newNode = createNode(iPtr);

    // Add the new node to the beginning of the linked list
    newNode->next = hashTable->lists[index];
    hashTable->lists[index] = newNode;
}

// Function to search for an item in the hashtable
node* search(hashtable* hashTable, const char* name) {
    int index = hashfunc(name, hashTable->size);
    node* current = hashTable->lists[index];

    // Traverse the linked list to find the item
    while (current != NULL) {
        if (strcmp(current->iPtr->name, name) == 0) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

// Function to delete a node with the given name from the hashtable
void deleteNode(hashtable* hashTable, const char* name) {
    int index = hashfunc(name, hashTable->size);
    node* current = hashTable->lists[index];

    // Check if the node to be deleted is the first node in the linked list
    if (current != NULL && strcmp(current->iPtr->name, name) == 0) {
        hashTable->lists[index] = current->next;
        free(current);
        return;
    }

    // Traverse the linked list to find and delete the node
    while (current != NULL && current->next != NULL) {
        if (strcmp(current->next->iPtr->name, name) == 0) {
            node* temp = current->next;
            current->next = current->next->next;
            free(temp);
            return;
        }
        current = current->next;
    }
}

// Function to get the length of the linked list at the specified index in the hashtable
int getListLength(hashtable* hashTable, int index) {
    int length = 0;
    node* current = hashTable->lists[index];

    // Traverse the linked list and count nodes
    while (current != NULL) {
        length++;
        current = current->next;
    }

    return length;
}

// Function to find the position of a node with the given name in its linked list
int findNodePosition(hashtable* hashTable, const char* name) {
    int index = hashfunc(name, hashTable->size);
    int position = 0;
    node* current = hashTable->lists[index];

    // Traverse the linked list and find the position of the node
    while (current != NULL && strcmp(current->iPtr->name, name) != 0) {
        position++;
        current = current->next;
    }

    return position;
}

// Function to get the position of an existing node in its linked list
int getPositionInList(hashtable* hashTable, const char* name, node* existingNode) {
    int index = hashfunc(name, hashTable->size);
    int position = 1; // Start from 1-based counting
    node* current = hashTable->lists[index];

    // Traverse the linked list and find the position of the existing node
    while (current != existingNode) {
        position++;
        current = current->next;
    }

    return position;
}

int main() {
    // Read the number of commands
    int n;
    scanf("%d", &n);

    // Create a hashtable for inventory
    hashtable* inventory = createHashTable(TABLESIZE);
    // Initialize total cash
    int totalCash = 100000;
    // Initialize total complexity
    int totalComplexity = 0;

    // Process each command
    for (int i = 0; i < n; ++i) {
        char command[MAXLEN + 1];
        scanf("%s", command);

        if (strcmp(command, "buy") == 0) {
            // Process buy command
            char name[MAXLEN + 1];
            int quantity, totalprice;
            scanf("%s %d %d", name, &quantity, &totalprice);

            // Search for the item in the inventory
            node* existingNode = search(inventory, name);

            // Update inventory based on whether the item already exists
            if (existingNode != NULL) {
                // Item already exists, update quantity and cash
                existingNode->iPtr->quantity += quantity;
                totalCash -= totalprice;
                // Update total complexity
                totalComplexity += getPositionInList(inventory, name, existingNode) + 1;
            }
            else {
                // Item doesn't exist, create a new item and insert into inventory
                item* newItem = createItem(name, quantity, 0);
                insert(inventory, newItem);
                totalCash -= totalprice;
                // Update total complexity
                totalComplexity += getListLength(inventory, hashfunc(name, inventory->size)) + 1;
            }

            // Print output for buy command
            printf("%s %d %d\n", name, quantity, totalCash);
        }
        else if (strcmp(command, "sell") == 0) {
            // Process sell command
            char name[MAXLEN + 1];
            int quantity;
            scanf("%s %d", name, &quantity);

            // Search for the item in the inventory
            node* existingNode = search(inventory, name);
            if (existingNode != NULL) {
                // Item exists, update quantity, cash, and total complexity
                int soldQuantity = (quantity < existingNode->iPtr->quantity) ? quantity : existingNode->iPtr->quantity;
                existingNode->iPtr->quantity -= soldQuantity;
                totalCash += (soldQuantity * existingNode->iPtr->saleprice);
                totalComplexity += 1;

                // Print output for sell command
                printf("%s %d %d\n", name, existingNode->iPtr->quantity, totalCash);
            }
        }
        else if (strcmp(command, "change_price") == 0) {
            // Process change_price command
            char name[MAXLEN + 1];
            int new_price;
            scanf("%s %d", name, &new_price);

            // Search for the item in the inventory
            node* existingNode = search(inventory, name);
            if (existingNode != NULL) {
                // Item exists, update sale price and print output
                existingNode->iPtr->saleprice = new_price;
                printf("%s %d %d\n", name, existingNode->iPtr->quantity, totalCash);
            }
        }
    }

    // Print total cash and total complexity at the end
    printf("%d\n%d\n", totalCash, totalComplexity);

    // Free allocated memory
    for (int i = 0; i < inventory->size; ++i) {
        node* current = inventory->lists[i];
        while (current != NULL) {
            node* temp = current;
            current = current->next;
            free(temp->iPtr);
            free(temp);
        }
    }
    free(inventory->lists);
    free(inventory);

    return 0;
}