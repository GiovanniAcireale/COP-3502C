// Giovanni Acireale, Lecture Notes, 9/6/23
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_CAP 10

typedef struct student {
	char* name;
	int grade;
};

typedef struct list {
	student* array;
	int size;
	int cap;
};

list* createList() {
	list* my_list = malloc(sizeof(list));
	my_list->array = malloc(DEFAULT_CAP * sizeof(student));
	my_list->size = 0;
	my_list->cap = DEFAULT_CAP;
	return my_list;
}

void append(list * my_list, char* name, int grade) {
	if(my_list->size == my_list->cap) {
		my_list->cap *= 2;
		my_list->array = realloc(my_list->array, my_list->cap * sizeof(student));
	}

	my_list->array[my_list->size].name = malloc(strlen(name) + 1);
	strcpy(my_list->array[my_list->size].name, name);
	my_list->array[my_list->size].grade = grade;
	my_list->size++;
}

void printList(list * my_list) {
	for(int i = 0; i < my_list->size; i++) {
		printf("%s %d\n", my_list->array[i].name, my_list->array[i].grade);
	}
}

void deleteList(list * my_list) {
	for(int i = 0; i < my_list->size; i++) {
		free(my_list->array[i].name);
	}
	free(my_list->array);
	free(my_list);
}

void removeByIndex(list * my_list, int index) {
	/*
	if(index < 0 || index >= my_list->size) {
		printf("Index out of bounds\n");
		return;
	}
	*/

	free(my_list->array[index].name);

	for(int i = index; i < my_list->size - 1; i++) {
		my_list->array[i].name = my_list->array[i + 1].name;
		my_list->array[i].grade = my_list->array[i + 1].grade;
	}

	if (my_list->cap != DEFAULT_CAP && my_list->cap >= my_list->size * 4) {
		my_list->cap /= 2;
		my_list->array = realloc(my_list->array, my_list->cap * sizeof(student));
	}

	my_list->size--;
}

int main() {
	list* my_list;
	my_list = createList();

	append(my_list, "a", 100);
	append(my_list, "b", 99);
	append(my_list, "c", 70);
	append(my_list, "d", 65);
	append(my_list, "e", 80);
	append(my_list, "f", 50);
	append(my_list, "g", 69);
	append(my_list, "h", 96);
	append(my_list, "i", 88);
	append(my_list, "j", 73);

	removeByIndex(my_list, 0);
}