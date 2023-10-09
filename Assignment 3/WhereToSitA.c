// Giovanni Acireale

// make a program that will take two positive integers n and p, 
// n (3 <= n <= 10) is the number of people attending the movie 
// and p (0 <= p <= n) is the number of people who do not want to sit together.

// then the next n lines will contain the names of the people attending the movie
// with one person described per line. These lines will describe the people in 
// alphabetical order by first name. Each name will be at most 19 characters long
// and will contain only UPPERCASE letters. using the following format: NAME 0/1
// where 0 represents someone who doesn't have popcorn and 1 represents someone who does.

// then the next p lines will indicate who does not want to sit together.
// each line will contain two names separated by a space.

// the output for program one will be a single integer representing the number valid orderings 
// (where the people who don't want to sit together aren't and everyone who 
// has popcorn has someone without to their left and right so that everyone 
// has access to someone with popcorn) of people attending the movie sitting 
// together in a single row, from left to right.

// example input:
// 5 2
// ALIA 1
// BELINDA 0
// CARLOS 0
// DANICA 0
// EDWARD 1
// ALIA CARLOS
// BELINDA EDWARD

// example output 1:
// 10

// Program 1: the number of different orderings (permutations) of the people satisfying all restricions 
// (everyone has access to popcorn and nobody is sitting next to someone they don't want to sit next to)
// use recursion

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
int validOrderingsHelper(Person* people, int n, int p, int* used, int* sitting, int* sittingNextTo);

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
	printf("%d\n", validOrderings(people, n, p));
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
	for (int i = 0; i < n; i++) {
		used[i] = 0;
		sitting[i] = 0;
		sittingNextTo[i] = 0;
	}
	int result = validOrderingsHelper(people, n, p, used, sitting, sittingNextTo);
	free(used);
	free(sitting);
	free(sittingNextTo);
	return result;
}

int validOrderingsHelper(Person* people, int n, int p, int* used, int* sitting, int* sittingNextTo) {
	int result = 0;
	if (p == 0) {
		return factorial(n);
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
			result += validOrderingsHelper(people, n, p - 1, used, sitting, sittingNextTo);
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
	return result;
}
