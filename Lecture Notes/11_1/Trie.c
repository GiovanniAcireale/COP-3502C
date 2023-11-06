// Giovanni Acireale, Lecture Notes, 11/01/23

#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node {
    int flag; // 1 if the word is in the dictionary
    // 0 if the word is not in
    Node* children[26];
    int count;
};

// Creates a node
Node* createNode() {
    Node* res = (Node*)malloc(sizeof(Node));
    res->flag = 0;
    for (int i = 0; i < 26; i++)
        res->children[i] = NULL;
    res->count = 0;
    return res;
}

// Insert a given word into the trie defined by a root
Node* insert(Node* root, char* word) {
    if (root == NULL)
        root = createNode();
    if (word[0] == '\0') {
        root->flag++; // store a multiplicity of a word
    }
    else {
        int ind = word[0] - 'a';
        root->children[ind] = insert(root->children[ind], word + 1);
    }
    // Inserted one more word into this trie *
    root->count++;
    return root;
}

// Remove a given word into the trie defined by a root
Node* removeTrie(Node* root, char* word, int* removed) {
    if (root == NULL)
        return root;
    if (word[0] == '\0') {
        if (root->flag != 0) {
            root->flag--;
            root->count--;
            *removed = 1;
        }
    }
    else {
        int ind = word[0] - 'a';
        root->children[ind] = removeTrie(root->children[ind], word + 1, removed);
        if (*removed) {
            root->count--;
        }
    }

    // 0 is not useful and non-zero is useful
    int useful = root->count;

    // was it useful?
    if (!useful) {
        free(root);
        return NULL;
    }

    return root;
}

// Prints all the words in a trie
void printAll(Node* root, char* word, int len) {
    if (root == NULL)
        return;

    // Handle all the children
    for (int i = 25; i >= 0; i--) {
        // Add the i-th character to the path
        word[len] = 'a' + i;

        // Go to the child at index i of the child array
        printAll(root->children[i], word, len + 1);
    }

    // Check if the word is in the trie
    if (root->flag == 1) {
        word[len] = 0;
        printf("%s\n", word);
    }
}

int main(void) {
    Node* root = NULL;
    root = insert(root, "cat");
    root = insert(root, "dog");
    root = insert(root, "dodge");
    root = insert(root, "doggy");
    root = insert(root, "dodgy");
    root = insert(root, "dogmatic");
    root = insert(root, "dogma");
    root = insert(root, "catch");
    root = insert(root, "cap");
    root = insert(root, "capitulate");
    root = insert(root, "nocap");


    int removed = 0;
    printf("The number of words in the trie is %d.\n", root->count);
    root = removeTrie(root, "doggy", &removed);
    printf("The number of words in the trie is %d.\n", root->count);

    char word[100 + 1];
    printAll(root, word, 0);

    return 0;
}