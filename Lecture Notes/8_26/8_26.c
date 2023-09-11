// Giovanni Acireale, Lecture Notes 8/28/23

/*
realloc
	Reallocate - allocate an old block of memory to some new size

	Parameters:
		1. Pointer to the old block of memory.
		2. # of bytes for the new size.

		arr = (int *) realloc(arr, 20*sizeof(int));
			Returns the location of the new block of memory.

	Possible Results
		1. Failure
			- NULL is returned
			- Old memory is still protected
		2. Success (Fast)
			- Old and new memory use the same address
		3. Success (Slow)
			- Old and new memory use different addresses
			- The program copies the old data into the new location
			- Old address is freed

Safe realloc
	int * tmp = (int*) realloc(arr, sizeof(int)*20);
	if(tmp != NULL) {tmp = 3;}

*/
#include <stdio.h>

//Dynamic Structs. (Classroom Example)

struct Student {
	int grade;
	char* name; // use dynamic blocks to save memory when possible

};

struct Class {
	struct Student* roster;
	int capacity;
	int enrolled;
	char* titles;
	struct Building* location;
};

// How would we determine the size of a structure?

// struct Class * my_class = (struct Class *) malloc(sizeof(struct Class));

// typedefs can be used to alias types
typedef struct Class Class;

// Instantiate a Class dynamically
// Initialize a Class
// Return it.
Class* createClass(int initial_cap) {
	Class* res = (Class*)malloc(sizeof(Class));
	res->capacity = initial_cap;
	(*res).enrolled = 0;
	res->roster = (struct Student*)malloc(sizeof(struct Student) * initial_cap);
	return res;
}

int main() {
	struct Class* my_class;
	my_class = createClass(250);

	// Free the class when I'm finished
	free(my_class);
	free(my_class->roster);

	return 0;
}