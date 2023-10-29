// Giovanni Acireale, Lecture Notes, 10/23/23
// AVL Tree
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Node Node;

struct Node {
    int value;
    Node* right, * left, * parent;
    int balanceFactor;
    int height;
};

Node* createNode(int value) {
    Node* res = (Node*)malloc(sizeof(Node));
    res->value = value;
    res->right = res->left = res->parent = NULL;
    res->balanceFactor = 0;
    res->height = 0;
    return res;
}

#define MAX(a,b) (((a)<(b)) ? (b) : (a))

int getHeight(Node* root) {
    if (root == NULL) return -1;
    return root->height;
}

void recomputeBalance(Node* root) {
    if (root == NULL) return;
    int rightHeight = getHeight(root->right);
    int leftHeight = getHeight(root->left);
    root->balanceFactor = leftHeight - rightHeight;
    root->height = 1 + MAX(rightHeight, leftHeight);
}

void rotateLeft(Node* root) {
    assert(root != NULL && root->right != NULL);
    Node* child = root->right;
    Node* parent = root->parent;
    Node* grandchild = child->left;

    // Top Edge
    child->parent = parent;
    if (parent != NULL) {
        if (parent->right == root) {
            parent->right = child;
        }
        else {
            parent->left = child;
        }
    }

    // Mid Edge (root and child)
    root->parent = child;
    child->left = root;

    // Bottom Edge (grandchild and root)
    root->right = grandchild;
    if (grandchild != NULL) {
        grandchild->parent = root;
    }
    recomputeBalance(root);
    recomputeBalance(child);
    recomputeBalance(parent);
}

void rotateRight(Node* root) {
    assert(root != NULL && root->left != NULL);
    Node* child = root->left;
    Node* parent = root->parent;
    Node* grandchild = child->right;

    // Top Edge
    child->parent = parent;
    if (parent != NULL) {
        if (parent->right == root) {
            parent->right = child;
        }
        else {
            parent->left = child;
        }
    }

    // Mid Edge (root and child)
    root->parent = child;
    child->right = root;

    // Bottom Edge (grandchild and root)
    root->left = grandchild;
    if (grandchild != NULL) {
        grandchild->parent = root;
    }

    recomputeBalance(root);
    recomputeBalance(child);
    recomputeBalance(parent);
}

void rebalance(Node* root) {
    if (root == NULL) return;
    if (root->balanceFactor == 2) {
        // LEFT
        if (root->left->balanceFactor == -1) {
            // RIGHT
            rotateLeft(root->left);
        }
        // LEFT
        rotateRight(root);

    }
    else if (root->balanceFactor == -2) {
        // RIGHT
        if (root->right->balanceFactor == 1) {
            // LEFT
            rotateRight(root->right);
        }
        // RIGHT
        rotateLeft(root);
    }
}

Node* insert(Node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }
    if (value < root->value) {
        root->left = insert(root->left, value);
        root->left->parent = root;
        recomputeBalance(root);
        if (root->balanceFactor > 1 || root->balanceFactor < -1) {
            rebalance(root);
            return root->parent;
        }
    }
    else if (value > root->value) {
        root->right = insert(root->right, value);
        root->right->parent = root;
        recomputeBalance(root);
        if (root->balanceFactor > 1 || root->balanceFactor < -1) {
            rebalance(root);
            return root->parent;
        }
    }
    // Either duplicate or no rotation was necessary
    return root;
}

void printPreOrder(Node* root) {
    if (root == NULL) return;
    printf("%d ", root->value);
    printPreOrder(root->left);
    printPreOrder(root->right);
}

int main(void) {
    Node* root = NULL;
    for (int i = 0; i < 16; i++) {
        root = insert(root, i + 1);
        printPreOrder(root);
        printf("\n");
    }
    printf("Hello World\n");
    return 0;
}