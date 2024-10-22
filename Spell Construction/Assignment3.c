// Giovanni Acireale, Assignment 3, 10/16/24

#include <stdio.h>
#include <string.h>

#define MAX_N 11
#define MAX_L 100

// Global variables to hold the best incantation and minimum length of the result
char best_incantation[1000];
int min_length = 1000;
int precomputed_overlap[MAX_N][MAX_N];  // 2D array to store precomputed overlaps

// Function to compute the maximum overlap between the suffix of string 'a' and the prefix of string 'b'
int compute_overlap(char* a, char* b, int L) {
    int max_overlap = 0;
    // Check all possible overlap lengths between the two strings
    for (int i = 1; i <= L; i++) {
        if (strncmp(a + L - i, b, i) == 0) {
            max_overlap = i;
        }
    }
    return max_overlap;
}

// Function to swap two integers (used in generating permutations)
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Recursive function to generate permutations and calculate the best incantation
void permute(int* perm, int n, int size, char sequences[MAX_N][MAX_L + 1], int N, int L) {
    if (n == size) {
        // Start with the first sequence in the current permutation
        char current[1000];
        strcpy(current, sequences[perm[0]]);
        int total_length = L;

        // Stitch together the sequences in the order of the current permutation
        for (int i = 1; i < N; i++) {
            int ovlp = precomputed_overlap[perm[i - 1]][perm[i]];
            // Append only the non-overlapping part of the next sequence
            strcat(current, sequences[perm[i]] + ovlp);
            total_length += L - ovlp;
        }

        // Check if the current incantation is the shortest or lexicographically smaller
        if (total_length < min_length || (total_length == min_length && strcmp(current, best_incantation) < 0)) {
            min_length = total_length;
            strcpy(best_incantation, current);
        }
        return;
    }

    // Generate all permutations by swapping elements
    for (int i = n; i < size; i++) {
        swap(&perm[n], &perm[i]);
        permute(perm, n + 1, size, sequences, N, L);
        swap(&perm[n], &perm[i]);
    }
}

// Precompute all overlaps between sequences (store them in the precomputed_overlap array)
void precompute_all_overlaps(char sequences[MAX_N][MAX_L + 1], int N, int L) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i != j) {
                precomputed_overlap[i][j] = compute_overlap(sequences[i], sequences[j], L);
            }
            else {
                precomputed_overlap[i][j] = 0;  // No overlap with itself
            }
        }
    }
}

// Function to find the shortest incantation that contains all the sequences
void find_shortest_incantation(char sequences[MAX_N][MAX_L + 1], int N, int L) {
    int perm[MAX_N];  // Array to track the indices for permutations
    for (int i = 0; i < N; i++) {
        perm[i] = i;
    }

    // Initialize the best incantation and its length to a large value
    min_length = 1000;
    best_incantation[0] = '\0';

    // Precompute overlaps between all pairs of sequences
    precompute_all_overlaps(sequences, N, L);

    // Generate permutations and compute the shortest incantation
    permute(perm, 0, N, sequences, N, L);

    // Output the shortest incantation found
    printf("%s\n", best_incantation);
}

int main() {
    int N, L;
    // Read the number of sequences (N) and their length (L)
    scanf("%d %d", &N, &L);

    char sequences[MAX_N][MAX_L + 1];  // Array to store the sequences
    for (int i = 0; i < N; i++) {
        // Read each sequence into the array
        scanf("%s", sequences[i]);
    }

    // Find and output the shortest incantation
    find_shortest_incantation(sequences, N, L);

    return 0;
}
