#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hash(char* str, int mod)
{
	long long int result = 0;
	for (int i = 0; str[i]; i++)
	{
		result *= 1337;
		result += str[i];
		result %= mod;
	}
	return (int)(result % mod);
}

void insert(char** arr, char* str, int size)
{
	int index = hash(str, size);
	int cIndex = index;
	printf("%s initially at %d\n", str, index);
	int count = 0;
	while (arr[cIndex])
	{
		count++;
		cIndex = (index + count * count) % size;
	}
	arr[cIndex] = _strdup(str);
	printf("%s at %d\n", str, cIndex);
}

void gen(char* str) {
	for (int i = 0; i < 6; i++)
		str[i] = rand() % 26 + 'a';
	str[6] = 0;
}

int main() {
	char* arr[13];
	for (int i = 0; i < 13; i++) arr[i] = NULL;
	insert(arr, "Alice", 13);
	insert(arr, "Bob", 13);
	insert(arr, "Carol", 13);
	insert(arr, "David", 13);
	char str[7];
	do {
		gen(str);
		printf("%s\n", str);
		if (hash(str, 13) == 10) break;
	} while (1);
	insert(arr, str, 13);
	return 0;
}
