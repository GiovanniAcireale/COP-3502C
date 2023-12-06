#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Include the string.h header file


typedef struct Node Node;

// Store the order of the letters
int perm[26];

// The struct of the trie node
struct Node {
    Node* children[26];
    int flag;
    int subTrieCount;
};

// Function to create a node
Node* createNode() {
    Node* res = (Node*)malloc(sizeof(Node));
    res->flag = 0;
    res->subTrieCount = 0;
    for (int i = 0; i < 26; i++) {
        res->children[i] = NULL;
    }
    return res;
}

// Function to insert a word into the trie
Node* insert(Node* root, char* word) {
    // Make a node if one does not exist
    if (root == NULL) {
        root = createNode();
    }

    // Update the number of words in this subtrie
    root->subTrieCount++;

    // Check if at the end of the string
    if (word[0] == '\0') {
        root->flag = 1;
        return root;
    }

    // Insert recursively 
    root->children[word[0] - 'a'] = insert(root->children[word[0] - 'a'], word + 1);

    // Return the resulting root of the trie
    return root;
}

// Function to get the k-th word from the trie
int getKth(Node* root, int k, char* res) {
    // Check if the trie is empty
    if (root == NULL) return 0;

    // Check if the trie is too small
    if (root->subTrieCount <= k) return 0;

    // Check if we are at the word
    if (k < root->flag) {
        res[0] = '\0';
        return 1;
    }

    // Adjust k by the number of times this word appears
    k -= root->flag;

    // Loop through all the children
    for (int i = 0; i < 26; i++) {
        res[0] = i + 'a';
        if (getKth(root->children[perm[i]], k, res + 1)) return 1;
        if (root->children[perm[i]])
            k -= root->children[perm[i]]->subTrieCount;
    }

    // Return that no children was found (somehow)
    return 0;
}

// The main function
int main(int argc, char** argv) {
    if (argc < 3) {
        fprintf(stderr, "Please provide the word file and the message file as input parameters.\n");
        return 1;
    }

    // Read in the list of words
    Node* root = NULL;
    FILE* ifp = fopen("input.txt", "r");  // Open the input file "input.txt"
    
    // Check if the file opened successfully
    if (ifp == NULL) {
        fprintf(stderr, "Error opening input file.\n");
        return 1;
    }

    char word[1000];
    while (EOF != fscanf(ifp, "%s", word)) {
        root = insert(root, word);
    }

    // Create the permutation of the alphabet
    for (int i = 0; i < 26; i++)
        perm[i] = i;

    // Read in all the commands
    fclose(ifp);
    ifp = fopen(argv[2], "r");
    while (EOF != fscanf(ifp, "%s", word)) {
        if (!strcmp(word, "READ")) {
            int index;
            fscanf(ifp, "%d", &index);
            getKth(root, index, word);
            printf("%s ", word);
        }
        else {
            char a, b;
            fscanf(ifp, " %c %c", &a, &b);
            int tmp = perm[a - 'a'];
            perm[a - 'a'] = perm[b - 'a'];
            perm[b - 'a'] = tmp;
        }
    }

    // End the message with a new line
    printf("\n");

    // Close the input file
    fclose(ifp);

    // Exit the program successfully (probably should have cleaned up memory...)
    return 0;
}
