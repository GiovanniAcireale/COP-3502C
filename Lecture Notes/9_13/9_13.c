// Giovanni Acireale, Lecture Notes, 9/13/23

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node * next;
	struct Node * prev;
} Node;

typedef struct List {
	Node * head;
	Node * tail;
} List;

void removeHead(List* lst);
void removeTail(List* lst);
Node * creatNode(int data);
void insertHead(List* lst, int data);
void insertTail(List* lst, int data);
void printList(List* lst);

void removeHead(List* lst) {
	if(lst == NULL || lst->head == NULL) return;

	// 1 node case check
	if(lst->head == lst->tail) {
		free(lst->head);
		lst->head = lst->tail = NULL;
		return;
	}

	lst->head = lst->head->next;
	free(lst->head->prev);
	lst->head->prev = NULL;
}

void removeTail(List* lst) {
	if(lst == NULL || lst->tail == NULL) return;

	// 1 node case check
	if(lst->head == lst->tail) {
		free(lst->tail);
		lst->head = lst->tail = NULL;
		return;
	}

	lst->tail = lst->tail->prev;
	free(lst->tail->next);
	lst->tail->next = NULL;
}

Node * creatNode(int data) {
	Node * res = (Node *)malloc(sizeof(Node));
	res->data = data;
	res->next = res->prev = NULL;
	return res;
}

void insertHead(List* lst, int data) {
	if (lst == NULL) return;

	// empty list case
	if (lst->head == NULL) {
		lst->head = lst->tail = createNode(data);
		return;
	}

	// connect the node to the list
	lst->head->prev = createNode(data);
	lst->head->prev->next = lst->head;

	// point to the new head
	lst->head = lst->head->prev;
}

void insertTail(List* lst, int data) {
	if (lst == NULL) return;

	// empty list case
	if (lst->head == NULL) {
		lst->head = lst->tail = createNode(data);
		return;
	}

	// connect the node to the list
	lst->tail->next = createNode(data);
	lst->tail->next->prev = lst->tail;

	// point to the new head
	lst->tail = lst->tail->prev;
}

void printList(List* lst) {
	Node * cur = lst->head;
	while (cur != NULL) {
		printf("%d <->", cur->data);
		cur = cur->next;
	}
	printf("NULL\n");
}

int main() {
	List lst;
	lst->head = lst->tail = NULL;

	for (int i = 0; i < 10; i++) {
		if (i % 2) {
			insertTail(&lst);
		} else {
			insertHead(&lst);
		}
		printList(&lst);
	}

	return 0;
}