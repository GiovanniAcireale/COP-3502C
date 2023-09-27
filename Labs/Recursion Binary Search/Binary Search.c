#include <stdio.h>
#include <stdlib.h>

#define DEFAULTVALUE 1e9

int smol(int a, int b) {
	if (a < b) {
		return a;
	}
	return b;
}

int search(int lo, int hi, int target, int *arr) {
	if (hi<lo) {
		return -1;
	}

	int mid = (lo + hi) / 2;
	int res = DEFAULTVALUE;

	if (arr[mid] >= target) {
		res = smol(arr[mid], search(lo, mid - 1, target, arr));
	}
	else {
		res = search(mid + 1, hi, target, arr);
	}

	return res;
}

int main() {
	int n;
	scanf("%d", &n);

	int *arr = malloc(n * sizeof(int));
	for(int i= 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}

	int q;
	scanf("%d", &q);

	for(int i = 0; i < q; i++) {
		int curTarg;
		scanf("%d", &curTarg);

		int res = search(0, n - 1, curTarg, arr);
		if (res == DEFAULTVALUE) {
			printf("Does not exist\n");
		}
		else {
			printf("%d\n", res);
		}
	}

	return 0;	
}