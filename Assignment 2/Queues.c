// Giovanni Acireale, Assignment 2, 9/18/23

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CUSTOMERS 500000
#define MAX_TICKETS 500
#define MAX_NAME 50
#define MAX_BOOTH 12

// 12 queues, 12 booths, b employees (0 < b <= 12)
// booths are numbered 1 to b
// all customers must arrive and stand in one of 12 queues before getting redirected to a booth
// let the number of queues that recieve at least one customer be k (k >= b)

// each queue is a linked list of customers
// each booth is a linked list of queues

// structs -----------------------------------------------------------------------------------------

// create a node struct for a linked list of customers
// this struct should have a pointer to a customer struct, and a pointer to a node struct
typedef struct node {
	customer* c;
	struct node* next;
} node;

// each customer has a name, number of tickets, line number, arrival time, and check out time
typedef struct customer {
	char name[MAX_NAME];
	int tickets;
	int line;
	int arrival;
	int checkout;
	struct customer* next;
} customer;

// create a struct to store a queue of customers. This struct should have two pointers – one to
// the front of the queue and one to the back, AND an integer field to store the size of the queue.
typedef struct queue {
	node* front;
	node* back;
	int size;
} queue;

// create a struct to store a booth. This struct should have a pointer to a queue struct, and a
// pointer to a booth struct
typedef struct booth {
	queue* q;
	struct booth* next;
} booth;

// function prototypes -----------------------------------------------------------------------------
void enqueue(queue* q, customer* c);
customer* dequeue(queue* q);
// Peek: Return to the front of the queue WITHOUT dequeuing
customer* peek(queue* q);
// Empty: Return 1 if the queue is empty, 0 otherwise
int empty(queue* q);
// Size: Return the size of the queue
int size(queue* q);
void addQueuetoBooth(booth* b, queue* q);
void addBooth(booth* b, queue* q);

// function -----------------------------------------------------------------------------

// enqueue: Add a customer to the back of the queue
void enqueue(queue* q, customer* c) {
	node* n = (node*)malloc(sizeof(node));
	n->c = c;
	n->next = NULL;
	if (q->size == 0) {
		q->front = n;
		q->back = n;
	}
	else {
		q->back->next = n;
		q->back = n;
	}
	q->size++;
}

// dequeue: Remove a customer from the front of the queue
customer* dequeue(queue* q) {
	if (q->size == 0) {
		return NULL;
	}
	node* n = q->front;
	customer* c = n->c;
	q->front = n->next;
	free(n);
	q->size--;
	return c;
}

// peek: Return to the front of the queue WITHOUT dequeuing
customer* peek(queue* q) {
	if (q->size == 0) {
		return NULL;
	}
	return q->front->c;
}

// empty: Return 1 if the queue is empty, 0 otherwise
int empty(queue* q) {
	if (q->size == 0) {
		return 1;
	}
	return 0;
}

// size: Return the size of the queue
int size(queue* q) {
	return q->size;
}

// addQueuetoBooth: Add a queue to the back of the booth
void addQueuetoBooth(booth* b, queue* q) {
	booth* temp = b;
	while (temp->next != NULL) {
		temp = temp->next;
	}
	booth* newBooth = (booth*)malloc(sizeof(booth));
	newBooth->q = q;
	newBooth->next = NULL;
	temp->next = newBooth;
}



// main -------------------------------------------------------------------------------------------
