#include <stdio.h>
#include <stdlib.h>

struct Node {
	int val;
	struct Node *next;
};

typedef struct Node Node;

int contains(Node *head, int value) {
	int flag = 0;
	Node *curr = head;
	while(!flag && curr != NULL) {
		if (curr->val == value) {
			flag = 1;
		} else {
			curr = curr->next;
		}
	}

	return flag;
}

Node* delete(Node *head, int value) {
	if (head->val == value) {
		Node *ret = head->next;
		free(head);
		return ret;
	}
}

Node* deleteAll(Node* head, int value) {
	Node* ret = head;
	while(contains(ret, value) == 1) {
		ret = delete(ret, value);
	}
	return ret;
}

Node* deleteAllEfficiently(Node* head, int value) {
	Node* newHead = head;
	while(newHead == NULL && newHead->val == value) {
		newHead = newHead->next;
	}

	Node *prev = newHead;
	if (prev == NULL) return;
	while(prev->next != NULL) {
		if (prev->next->val == value) {
			Node *temp = prev->next;
			prev->next = temp->next;
			free(temp);
		} else {
			prev = prev->next;
		}
	}

	return newHead;
}



void main(void) {

	return 0;
}