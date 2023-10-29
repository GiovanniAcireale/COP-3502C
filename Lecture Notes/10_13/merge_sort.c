// This program demonstrates the merge sort algorithm
// Header file includes
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define DEFAULT_N 10

// The merge sort function
// Input the array and the size of the array
void merge_sort(int* arr, int n) {
	// Base case
	if (n <= 1) return;

	// Compute the number of half the array
	int n2 = n / 2;

	merge_sort(arr, n2);
	merge_sort(arr + n2, n - n2);

	int* tmp = (int*)malloc(sizeof(int) * n);
	int fptr = 0; // front of the first half
	int bptr = n2; // front of the back half

	for (int i = 0; i < n; i++) {
		if (fptr == n2) {
			// front is empty
			tmp[i] = arr[bptr];
			bptr++;
		}
		else if (bptr == n) {
			// back is empty
			tmp[i] = arr[fptr];
			fptr++;
		}
		else if (arr[fptr] < arr[bptr]) {
			// front was smaller than the back
			tmp[i] = arr[fptr];
			fptr++;
		}
		else {
			// back was good enough
			tmp[i] = arr[bptr];
			bptr++;
		}
	}

	// Move the temp values into the orignal array
	for (int i = 0; i < n; i++) {
		arr[i] = tmp[i];
	}

	// Remove the temp array
	free(tmp);
}

void gen_array(int* arr, int n) {
	// generate a random array of size n
	for (int i = 0; i < n; i++)
		arr[i] = rand() % 101;
}

void print_array(int* arr, int n) {
	for (int i = 0; i < n; i++) {
		printf("%d", arr[i]);
		if (i == n - 1) printf("\n");
		else printf(" ");
	}
}

void verify_sorted(int* arr, int n) {
	// assert will kill the program if our sort was invalid
	for (int i = 0; i < n - 1; i++)
		assert(arr[i] <= arr[i + 1]);
}

int main(int argc, char** argv) {

	int n = DEFAULT_N;

	if (argc > 1) n = atoi(argv[1]); // make the size of the array

	// whatever number we passed in
	int* arr = (int*)malloc(n * sizeof(int));

	gen_array(arr, n);
	print_array(arr, n);
	merge_sort(arr, n);
	print_array(arr, n);
	verify_sorted(arr, n);
	free(arr);

	return 0;
}