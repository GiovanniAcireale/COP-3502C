#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
int main() {
	int N = 20;

	srand(clock());

	// make a permutation of N values
	int * perm = (int *) malloc(N * sizeof(int));
	for (int i = 0; i < N; i++) {
		perm[i] = i;
	}
	for (int i = 0; i < N; i++) {
		// grab an index 0 or greater than i
		int j = (rand() % (N - i)) + i;

		// swap perm[i] and perm[j]
		int temp = perm[i];
		perm[i] = perm[j];
		perm[j] = temp;
	}

	clock_t start = clock();

	// 0(i) [best case: at the beginning]
	// 0(N) [worst case: at the end]
	// 0(N/2) [average case: in the middle] *** not ideal
	// 0(N) [average case weighted sum] *** ideal
	// average analysis:
	//   SUM (steps taken * probability)
	//   AVG = 1(1/N) + 2(1/N) + 3(1/N) + ... + N(1/N)
	//       = (1 + 2 + 3 + ... + N)(1/N)
	//       = (N(N+1)/2)(1/N)
	//       = (N+1)/2
	for (int i = 0; i < N; i++) {
		if (perm[i] == 0) {
			printf("%d is at location %d\n", perm[i], i);
			break;
		}
	}

	clock_t end = clock();



}
*/

int main() {
	int i = 0, j = 0;

	// 0(N)
	while (i < N) {
		while (j < N) {
			j++;
		}
		i++;
	}

	// Array List
	// runtime from a single insertion into an array list
	// N elements currently inside
	// best: 0(i)
	// average: 0(i)
	// worst: 0(N) [expansion]


	return 0;
}