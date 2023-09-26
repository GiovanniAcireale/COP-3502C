// Giovanni Acireale, Lecture Notes, 9/8/23
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

// Linked List 2 Electric Boogaloo

typedef struct Node Node;
typedef struct LL LL;

struct Node {
	int data;
	Node* next;
};

struct LL {
	Node * head;
	int num_nodes;
};

// Head insertion: new node x
// create node 'x', and insert it at the head of the list 
// (i.e. make it the new head of the list)

void headInsertion(LL* list, int data) {
	Node * newNode = (Node *)malloc(sizeof(Node));

	newNode->data = data;
	newNode->next = list->head;
	list->head = newNode;
	list->num_nodes++;
}

// Tail insertion: new node x
// create node 'x', and insert it at the tail of the list
// (i.e. make it the new tail of the list)

void tailInsertion(LL* list, int data) {
	// create new node and set current location to head
	Node * newNode = (Node *)malloc(sizeof(Node));
	Node * currentLocation = list->head;

	// set data and next pointer of new node
	newNode->data = data;
	newNode->next = NULL;

	// if list is empty, make new node the head
	if (list->head == NULL) {
		list->head = newNode;
		list->num_nodes++;
		return;
	}

	// iterate through list until we reach the end
	while (currentLocation->next != NULL) {
		currentLocation = currentLocation->next;
	}

	currentLocation->next = newNode;
	list->num_nodes++;
}

// print list by iterating through the list and printing each node's data

void printList(LL list) {
	Node * currentLocation = list.head;
	while (currentLocation != NULL) {
		printf("%d\n", currentLocation->data);
		currentLocation = currentLocation->next;
	}

	printf("Number of nodes: %d\n", list.num_nodes);
}

void cleanList(LL* list) {
	Node * currentLocation = list->head;
	Node * nextLocation = NULL;

	while (currentLocation != NULL) {
		nextLocation = currentLocation->next;
		free(currentLocation);
		currentLocation = nextLocation;
	}

	list->head = NULL;
	list->num_nodes = 0;
}

void main(void) {
	/*LL list;

	// initialize list
	list.head = NULL;
	list.num_nodes = 0;

	// Functioning Head Insertion
	headInsertion(&list, 5);
	headInsertion(&list, 4);
	headInsertion(&list, 3);
	headInsertion(&list, 2);
	headInsertion(&list, 1);

	// Functioning Tail Insertion
	tailInsertion(&list, 5);
	tailInsertion(&list, 4);
	tailInsertion(&list, 3);
	tailInsertion(&list, 2);
	tailInsertion(&list, 1);


	// print list
	printList(list);

	// clean list
	cleanList(&list);
	*/



	return 0;
}