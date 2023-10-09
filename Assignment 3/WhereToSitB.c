// Program 2: the first ordering in lexicographical order of the people satisfying all restrictions
// (everyone has access to popcorn and nobody is sitting next to someone they don't want to sit next to)
// use backtracking

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10
#define MAX_NAME 19

typedef struct {
	char name[MAX_NAME];
	int popcorn;
} Person;

int factorial(int n);
int validOrderings(Person* people, int n, int p);
int validOrderingsHelper(Person* people, int n, int p, int* used, int* sitting, int* sittingNextTo, int* result);

int main(int argc, char* argv[]) {
	int n, p;
	scanf("%d %d", &n, &p);
	Person* people = (Person*)malloc(sizeof(Person) * n);
	for (int i = 0; i < n; i++) {
		scanf("%s %d", people[i].name, &people[i].popcorn);
	}
	char name1[MAX_NAME], name2[MAX_NAME];
	for (int i = 0; i < p; i++) {
		scanf("%s %s", name1, name2);
	}
	validOrderings(people, n, p);
	free(people);
	return 0;
}

int factorial(int n) {
	if (n == 0) {
		return 1;
	}
	return n * factorial(n - 1);
}

int validOrderings(Person* people, int n, int p) {
	int* used = (int*)malloc(sizeof(int) * n);
	int* sitting = (int*)malloc(sizeof(int) * n);
	int* sittingNextTo = (int*)malloc(sizeof(int) * n);
	int* result = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) {
		used[i] = 0;
		sitting[i] = 0;
		sittingNextTo[i] = 0;
		result[i] = 0;
	}
	validOrderingsHelper(people, n, p, used, sitting, sittingNextTo, result);
	free(used);
	free(sitting);
	free(sittingNextTo);
	free(result);
	return 0;
}

int validOrderingsHelper(Person* people, int n, int p, int* used, int* sitting, int* sittingNextTo, int* result) {
	if (p == 0) {
		for (int i = 0; i < n; i++) {
			printf("%s ", people[result[i]].name);
		}
		printf("\n");
		return 1;
	}
	for (int i = 0; i < n; i++) {
		if (used[i] == 0) {
			used[i] = 1;
			sitting[i] = 1;
			if (i > 0) {
				sittingNextTo[i - 1] = 1;
			}
			if (i < n - 1) {
				sittingNextTo[i + 1] = 1;
			}
			result[n - p] = i;
			if (validOrderingsHelper(people, n, p - 1, used, sitting, sittingNextTo, result) == 1) {
				return 1;
			}
			used[i] = 0;
			sitting[i] = 0;
			if (i > 0) {
				sittingNextTo[i - 1] = 0;
			}
			if (i < n - 1) {
				sittingNextTo[i + 1] = 0;
			}
		}
	}
	return 0;
}