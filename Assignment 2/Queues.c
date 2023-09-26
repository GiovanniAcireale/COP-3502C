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
// all customers must arrive ad stand in one of 12 queues before getting redirected to a booth
// let the number of queues that recieve at least one customer be k (k >= b)

// each queue is a linked list of customers
// each booth is a linked list of queues

// create a node struct for a linked list of customers
// this struct should have a pointer to a customer struct, and a pointer to a node struct

typedef struct node {
	customer* c;
	struct node* next;
} node;


// each customer has a name, number of tickets, line number, and arrival time

typedef struct customer {
	char name[MAX_NAME];
	int tickets;
	int line;
	int arrival;
	struct customer* next;
} customer;

// each booth has a number and a queue of customers
// this struct should have a pointer to the front of the queue, and a pointer to the back of the queue
// and an integer to store the size of the queue

typedef struct queue {
	node* front;
	node* back;
	int size;
} queue;

typedef struct booth {
	int num;
	queue* head;
	queue* tail;
	struct booth* next;
} booth;

// global variables
int n, b, k; // number of customers, number of booths, number of queue
customer* customers[MAX_CUSTOMERS]; // array of pointers to customers
booth* booths[MAX_BOOTH]; // array of pointers to booths

// functions
// create a new customer using dynamic memory allocation
customer* newCustomer(char* name, int tickets, int line, int arrival) {
	customer* c = (customer*)malloc(sizeof(customer));
	strcpy(c->name, name);
	c->tickets = tickets;
	c->line = line;
	c->arrival = arrival;
	c->next = NULL;
	return c;
}

// https://www.youtube.com/watch?v=YjxKYxpf51E