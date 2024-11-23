/* COP 3502C Assignment 5
This program is written by: Giovanni Acireale */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 25  // Maximum length for a vehicle owner's name

// Struct to define a node in the binary search tree (BST)
typedef struct Node {
    char ownerName[MAX_NAME_LEN];  // Vehicle owner's name
    int fineAmount;                // Fine amount associated with the owner
    struct Node* left;             // Pointer to the left child node
    struct Node* right;            // Pointer to the right child node
} Node;

// Function prototypes for BST operations
Node* addOwner(Node* root, const char* name, int fine, int* depth);
Node* adjustFine(Node* root, const char* name, int fine, int* isRemoved, int* depth);
Node* findOwner(Node* root, const char* name, int* depth);
int getTreeHeight(Node* root);
void printBalanceStatus(Node* root);
int calculateTotalFines(Node* root);
int getNodeCount(Node* root);
void calculateFinesBelow(Node* root, const char* name, int* totalFine);
void releaseMemory(Node* root);
void executeCommand(char command[], Node** root);

// Function to add a new owner or update fine if owner exists
Node* addOwner(Node* root, const char* name, int fine, int* depth) {
    if (!root) {
        Node* newOwner = (Node*)malloc(sizeof(Node));
        strcpy(newOwner->ownerName, name);
        newOwner->fineAmount = fine;
        newOwner->left = newOwner->right = NULL;
        printf("%s %d %d\n", name, fine, *depth);
        return newOwner;
    }
    (*depth)++;
    if (strcmp(name, root->ownerName) < 0) {
        root->left = addOwner(root->left, name, fine, depth);
    }
    else if (strcmp(name, root->ownerName) > 0) {
        root->right = addOwner(root->right, name, fine, depth);
    }
    else {
        root->fineAmount += fine;
        printf("%s %d %d\n", name, root->fineAmount, *depth);
    }
    return root;
}

// Helper function to locate the maximum node in a subtree
Node* getMaxNode(Node* root) {
    while (root->right) root = root->right;
    return root;
}

// Function to deduct fine or remove owner if fine reaches zero
Node* adjustFine(Node* root, const char* name, int fine, int* isRemoved, int* depth) {
    if (!root) {
        printf("%s not found\n", name);
        return NULL;
    }
    (*depth)++;
    if (strcmp(name, root->ownerName) < 0) {
        root->left = adjustFine(root->left, name, fine, isRemoved, depth);
    }
    else if (strcmp(name, root->ownerName) > 0) {
        root->right = adjustFine(root->right, name, fine, isRemoved, depth);
    }
    else {
        root->fineAmount -= fine;
        if (root->fineAmount <= 0) {
            printf("%s removed\n", name);
            *isRemoved = 1;
            if (!root->left) {
                Node* rightChild = root->right;
                free(root);
                return rightChild;
            }
            else if (!root->right) {
                Node* leftChild = root->left;
                free(root);
                return leftChild;
            }
            else {
                Node* maxNode = getMaxNode(root->left);
                strcpy(root->ownerName, maxNode->ownerName);
                root->fineAmount = maxNode->fineAmount;
                root->left = adjustFine(root->left, maxNode->ownerName, maxNode->fineAmount, isRemoved, depth);
            }
        }
        else {
            printf("%s %d %d\n", name, root->fineAmount, *depth);
        }
    }
    return root;
}

// Function to search for an owner, printing fine amount and depth if found
Node* findOwner(Node* root, const char* name, int* depth) {
    if (!root) {
        printf("%s not found\n", name);
        return NULL;
    }
    (*depth)++;
    if (strcmp(name, root->ownerName) < 0) {
        return findOwner(root->left, name, depth);
    }
    else if (strcmp(name, root->ownerName) > 0) {
        return findOwner(root->right, name, depth);
    }
    else {
        printf("%s %d %d\n", name, root->fineAmount, *depth);
        return root;
    }
}

// Function to compute the height of the tree
int getTreeHeight(Node* root) {
    if (!root) return -1;
    int leftHeight = getTreeHeight(root->left);
    int rightHeight = getTreeHeight(root->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// Function to print balance status of the tree
void printBalanceStatus(Node* root) {
    if (!root) {
        printf("Tree is empty\n");
        return;
    }
    int leftHeight = getTreeHeight(root->left);
    int rightHeight = getTreeHeight(root->right);
    printf("left height = %d right height = %d ", leftHeight, rightHeight);
    if (leftHeight == rightHeight) {
        printf("balanced\n");
    }
    else {
        printf("not balanced\n");
    }
}

// Function to calculate total fines below a certain name
void calculateFinesBelow(Node* root, const char* name, int* totalFine) {
    if (!root) return;
    if (strcmp(root->ownerName, name) < 0) {
        *totalFine += root->fineAmount;
        calculateFinesBelow(root->right, name, totalFine);
        calculateFinesBelow(root->left, name, totalFine);
    }
    else {
        calculateFinesBelow(root->left, name, totalFine);
    }
}

// Function to calculate the sum of all fines in the BST
int calculateTotalFines(Node* root) {
    if (!root) return 0;
    return root->fineAmount + calculateTotalFines(root->left) + calculateTotalFines(root->right);
}

// Function to count the number of nodes in the BST
int getNodeCount(Node* root) {
    if (!root) return 0;
    return 1 + getNodeCount(root->left) + getNodeCount(root->right);
}

// Function to release memory of all nodes in the BST
void releaseMemory(Node* root) {
    if (!root) return;
    releaseMemory(root->left);
    releaseMemory(root->right);
    free(root);
}

// Function to process commands and execute corresponding functions
void executeCommand(char command[], Node** root) {
    if (strcmp(command, "add") == 0) {
        char name[MAX_NAME_LEN];
        int fine, depth = 0;
        scanf("%s %d", name, &fine);
        *root = addOwner(*root, name, fine, &depth);
    }
    else if (strcmp(command, "deduct") == 0) {
        char name[MAX_NAME_LEN];
        int fine, isRemoved = 0, depth = 0;
        scanf("%s %d", name, &fine);
        *root = adjustFine(*root, name, fine, &isRemoved, &depth);
    }
    else if (strcmp(command, "search") == 0) {
        char name[MAX_NAME_LEN];
        int depth = 0;
        scanf("%s", name);
        findOwner(*root, name, &depth);
    }
    else if (strcmp(command, "average") == 0) {
        int totalFine = calculateTotalFines(*root);
        int count = getNodeCount(*root);
        double average = count > 0 ? (double)totalFine / count : 0.0;
        printf("%.2f\n", average);
    }
    else if (strcmp(command, "height_balance") == 0) {
        printBalanceStatus(*root);
    }
    else if (strcmp(command, "calc_below") == 0) {
        char name[MAX_NAME_LEN];
        int totalFine = 0;
        scanf("%s", name);
        calculateFinesBelow(*root, name, &totalFine);
        printf("%d\n", totalFine);
    }
}

// Main function to initiate input processing and BST operations
int main() {
    int numCommands;
    scanf("%d", &numCommands);
    Node* root = NULL;
    for (int i = 0; i < numCommands; i++) {
        char command[20];
        scanf("%s", command);
        executeCommand(command, &root);
    }
    releaseMemory(root);
    return 0;
}
