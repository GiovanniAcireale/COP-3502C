// Giovanni Acireale, Recursion/Binary Search Lab, 9/26/23
/*
#include <stdio.h>
#include <stdlib.h>

char options[] = { 'a', 'b', 'c', 'd', 'e', 'r' };

#define MAXOPTIONS 6

int perm[MAXOPTIONS], used[MAXOPTIONS];

int count = 0;

void makePerms(int idx) {
	if (idx == MAXOPTIONS) {
		// processing permutation
		count++;
		printf("%d: ", count);
		for (int i = 0; i < MAXOPTIONS; i++) {
			printf("%c", options[perm[i]]);
		}
		printf("\n");

		return;
	}

	for (int i = 0; i < MAXOPTIONS; i++) {
		if (used[i] == 0) {
			used[i] = 1;
			perm[idx] = i;
			makePerms(idx + 1);
			used[i] = 0;
			perm[idx] = -1;
		}
	}
}

int main() {
	for(int i = 0; i < MAXOPTIONS; i++) {
		perm[i] = -1;
		used[i] = 0;
	}

	return 0;
}
*/