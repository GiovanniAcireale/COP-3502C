#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_N 500

int main(int argc, char** argv) {
	int ans = 0;
	int n = DEFAULT_N;
	for (int i = 0; i < argc; i++) {
		printf("%s ", argv[i]);
	}
	printf("\n");

	if (argc == 2) {
		n = atoi(argv[1]);
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for(int k = 0; k < n; k++) {
				ans += rand();
			}
		}
	}

	return 0;
}

/*

// what will the runtime of the following snippet be?

for (int i = 1; i < n; i *= 2) {
	ans++;
}

// no clue...

// i ~= 2^iter
// i ~= n (when done)
// 2^iter ~= n
// log_2(2^iter) ~= log_2(n) ---> log_2 represents log base 2
// iter * log_2(2) ~= log_2(n)
// iter ~= log_2(n)

// BigTheta(log(n))

// what will the runtime of the following snippet be?

for (int i = 0; i < n; i++) {
	for (int j = 0; j < n; j++) {
		for(int k = 0; k < n; k++) {
			ans++;
		}
	}
}

// BigTheta(n^3)?

// Remember these:                                                                                                   n
* Sumations:   ---------------------> n^rsum_i=1 is the text equivalent of the summation symbol from i = 1 to n:   rsum
* n^rsum_i=1 1 = n                                                                                                  i=1
* n^rsum_i=1 i = (n * (n + 1)) / 2
* n^rsum_i=1 i^2 = (n * (n + 1) * (2n + 1)) / 6
* n^rsum_i=1 i^3 = (n^2 * (n + 1)^2) / 4


// what will the runtime of the following snippet be?

for (int i = 0; i < n; i++) {
	for (int j = 0; j < n; j++) {
		ans++;
	}
}
















*/