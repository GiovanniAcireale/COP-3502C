// Giovanni Acireale, Assignment 5, 11/13/23
/*
Background Story

Our theater is now experimenting with pie shaped projectors (turned out to be a big fail!)
Instead, they are going to copy the Universal Cinema Foundation and start a rewards program.
Each guest gets 1 loyalty point for each dollar they spend at the theater. Over time, guests may
gain loyalty points, use loyalty points to redeem prizes or query the number of loyalty points
they have. On occasion, a guest may get very upset at the theater (maybe they showed the Taylor
Swift movie one too many times), and request to be removed from the loyalty program. One
strange request the theater wants the program to handle is a query of how many users have
names that come alphabetically before a particular user.
Since the theater knows you are learning about binary search trees in class, they would like for
you to implement this functionality via a binary search tree of nodes, where the nodes are
compared via the name of the customer stored in the node, in alphabetical order.

Problem

Write a program that reads in input corresponding to various changes and queries to the theater's
loyalty program and prints out corresponding messages for each of the input commands. Here is
an informal list of each of the possible commands in the input:
(1) Add Loyalty Points to a particular customer.
(2) Subtract Loyalty Points from a particular customer.
(3) Delete a particular customer.
(4) Search for a particular customer in the binary search tree. If the customer is found, report
both their number of loyalty points and their depth in the tree (distance from the root in # of links
to follow.)
(5) Count the number of customers whose names come alphabetically before a particular
customer.
At the very end of the input, your program should store pointers to each struct storing customer
data and sort that data by loyalty points, from highest to lowest, breaking ties alphabetically. (For
two customers with the same number of loyalty points, the one whose name comes first
alphabetically should be listed first.) This data should be sorted via either Merge Sort or Quick
Sort.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct customer {
    char* name;
    int points;
    int depth;
    struct customer* left;
    struct customer* right;
} customer;

// Function prototypes
customer* addCustomer(customer* root, char* name, int points, int depth);
customer* deleteCustomer(customer* root, char* name, int* depth);
customer* findCustomer(customer* root, char* name, int* depth);
customer* findMin(customer* root);
int countCustomers(customer* root, char* name);
void printCustomers(customer* root);
void freeCustomers(customer* root);
void updateDepth(customer* root, int depth);

// Main function
int main() {
    int count, points, depth = 0;
    char name[100];
    char command[100];
    customer* root = NULL, * temp = NULL;

    scanf("%d", &count);

    for (int i = 0; i < count; i++) {
        scanf("%s", command);

        if (strcmp(command, "add") == 0) {
            scanf("%s %d", name, &points);
            root = addCustomer(root, name, points, 0);
            temp = findCustomer(root, name, NULL);
            printf("%s %d\n", name, temp->points);
        }
        else if (strcmp(command, "sub") == 0) {
            scanf("%s %d", name, &points);
            temp = findCustomer(root, name, NULL);
            if (temp == NULL) {
                printf("%s not found\n", name);
            }
            else {
                temp->points -= points;
                if (temp->points < 0) {
                    temp->points = 0;
                }
                printf("%s %d\n", name, temp->points);
            }
        }
        else if (strcmp(command, "del") == 0) {
            scanf("%s", name);
            root = deleteCustomer(root, name, &depth);
            printf("%s deleted\n", name);
        }
        else if (strcmp(command, "search") == 0) {
            scanf("%s", name);
            temp = findCustomer(root, name, &depth);
            if (temp == NULL) {
                printf("%s not found\n", name);
            }
            else {
                printf("%s %d %d\n", name, temp->points, depth);
            }
        }
        else if (strcmp(command, "count_smaller") == 0) {
            scanf("%s", name);
            int count = countCustomers(root, name);
            printf("%d\n", count);
        }
    }

    printCustomers(root);
    freeCustomers(root);

    return 0;
}

customer* addCustomer(customer* root, char* name, int points, int depth) {
    if (root == NULL) {
        root = malloc(sizeof(customer));
        root->name = malloc(sizeof(char) * (strlen(name) + 1));
        strcpy(root->name, name);
        root->points = points;
        root->depth = depth;
        root->left = NULL;
        root->right = NULL;
    }
    else if (strcmp(name, root->name) < 0) {
        root->left = addCustomer(root->left, name, points, depth + 1);
    }
    else if (strcmp(name, root->name) > 0) {
        root->right = addCustomer(root->right, name, points, depth + 1);
    }
    else {
        root->points += points;
    }

    return root;
}

customer* deleteCustomer(customer* root, char* name, int* depth) {
    if (root == NULL) {
        return NULL;
    }

    if (strcmp(name, root->name) < 0) {
        (*depth)++;
        root->left = deleteCustomer(root->left, name, depth);
    }
    else if (strcmp(name, root->name) > 0) {
        (*depth)++;
        root->right = deleteCustomer(root->right, name, depth);
    }
    else {
        if (root->left == NULL) {
            customer* temp = root->right;
            free(root->name);
            free(root);

            // Adjust depth for the new root
            if (temp != NULL) {
                temp->depth = 0;
            }

            return temp;
        }
        else if (root->right == NULL) {
            customer* temp = root->left;
            free(root->name);
            free(root);

            // Adjust depth for the new root
            if (temp != NULL) {
                temp->depth = 0;
            }

            return temp;
        }

        // Find the minimum node in the right subtree
        customer* temp = findMin(root->right);
        free(root->name);
        root->name = malloc(sizeof(char) * (strlen(temp->name) + 1));
        strcpy(root->name, temp->name);
        root->points = temp->points;

        // Delete the minimum node in the right subtree
        root->right = deleteCustomer(root->right, temp->name, depth);
    }

    return root;
}

customer* findCustomer(customer* root, char* name, int* depth) {
    if (root == NULL) {
        if (depth != NULL) {
            *depth = -1;
        }
        return NULL;
    }

    if (strcmp(name, root->name) < 0) {
        if (depth != NULL) {
            *depth = root->depth;
        }
        return findCustomer(root->left, name, depth);
    }
    else if (strcmp(name, root->name) > 0) {
        if (depth != NULL) {
            *depth = root->depth;
        }
        return findCustomer(root->right, name, depth);
    }
    else {
        if (depth != NULL) {
            *depth = root->depth;
        }
        return root;
    }
}

customer* findMin(customer* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

int countCustomers(customer* root, char* name) {
    if (root == NULL) {
        return 0;
    }

    if (strcmp(name, root->name) <= 0) {
        return countCustomers(root->left, name);
    }
    else {
        return 1 + countCustomers(root->right, name) + countCustomers(root->left, name);
    }
}

void printCustomers(customer* root) {
    if (root != NULL) {
        printCustomers(root->left);
        printf("%s %d\n", root->name, root->points);
        printCustomers(root->right);
    }
}

void freeCustomers(customer* root) {
    if (root != NULL) {
        freeCustomers(root->left);
        freeCustomers(root->right);
        free(root->name);
        free(root);
    }
}

void updateDepth(customer* root, int depth) {
    if (root != NULL) {
        root->depth = depth;
        updateDepth(root->left, depth + 1);
        updateDepth(root->right, depth + 1);
    }
}



