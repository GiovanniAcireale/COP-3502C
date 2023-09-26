// Giovanni Acireale, Lecture Notes, 9/18/23

// Recursion: a function that calls itself

/*
Recursion - self defined behaviour

	1. Data Recursion
		i.e Nodes in a linked list

	2. Function Recursion
		i.e functions that call themselves

	3. Mathmatical expression Recursion
		i.e Factorials like f(x) = x * f(x-1)

2 Major components of Recursion
	1. Base Case
		non-recursive behaviour
			NULL or tail of linked list

	2. Recursive Case
		recursive behaviour
			non-NULL or non-tail of linked list

		Recursive Case must always lead to the Base Case
			otherwise infinite loop

// Example of a recursive function
// Returns head of linked list
Node * removeTail(Node * head) {
	if (head == NULL) {
		return NULL;
	}
	if (head->next == NULL) {
		free(head);
		return NULL;
	}
	head->next = removeTail(head->next);
	return head;
}

*/