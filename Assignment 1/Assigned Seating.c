// Giovanni Acireale, Assignment 1, 9/11/23

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*

Write a program that can allow for people to buy consecutive seats in a row (if available) and
look up who owns the seat at a particular spot in a row. You should assume that the theater
starts with every seat available for purchase.

Input:

BUY <ROW> <START> <END> <NAME>
	* This means the user with the given <NAME> will try to purchase the seats in the
	given <ROW>. They want the seats with numbers ranging from <START> to
	<END> inclusive.
	* You are guaranteed that <START> will be at most <END>.
	* If any other user owns at least one seat in this range, the purchase should NOT
	go through.

LOOKUP <ROW> <SEAT>
	* This means that we need to determine which user, if any, purchased the seat with
	the number <SEAT> in the given <ROW>.

QUIT
	* This should terminate the program and clean up any memory.

<ROW>, <START>, <END>, and <SEAT> will all be positive integers in the range of 1 to 100,000,
inclusive. The <NAME> will be an alphabetic string of at most 50 characters.

Output:

For each BUY input, output a single line containing the word “SUCCESS” if the purchase was
successful, and “FAILURE” otherwise. For each LOOKUP input, output a single line containing
solely the name of the user that owns the seat, if the seat is owned and “No one”, if the seat is
unowned.

*/

typedef struct Seat Seat;
typedef struct Row Row;

// a row will consist of a number and a list of seats per number
struct Row {
	int rowNum;
	Seat* seatList;
	Row* next;
};

// a seat will consist of a number and a name
struct Seat {
	int seatNum;
	char* name;
	Seat* next;
};

// function prototypes
void buy(Row* rowList, int row, int start, int end, char* name);
void lookup(Row* rowList, int row, int seat);
void quit(Row* rowList);

// buy seats
void buy(Row* rowList, int row, int start, int end, char* name) {
	// check if row exists
	Row* currentRow = rowList->next;
	
	// if row list is empty, create new row
	if (currentRow == NULL) {
		Row* newRow = (Row*)malloc(sizeof(Row));
		newRow->rowNum = row;
		newRow->next = NULL;
		rowList->next = newRow;
		currentRow = newRow;
	}
	
	// if row exists, look for each seat between start and end
	while (currentRow->next != NULL) {
		if (currentRow->rowNum == row) {
			Seat* currentSeat = currentRow->seatList;
			while (currentSeat->next != NULL) {
				if (currentSeat->seatNum >= start && currentSeat->seatNum <= end) {
					printf("FAILURE\n");
					return;
				}
				currentSeat = currentSeat->next;
			}
		}
		currentRow = currentRow->next;
	}
	
	// if row does not exist, create new row
	Row* newRow = (Row*)malloc(sizeof(Row));
	newRow->rowNum = row;
	newRow->next = NULL;
	currentRow->next = newRow;
	currentRow = newRow;
	
	// create new seats
	for (int i = start; i <= end; i++) {
		Seat* newSeat = (Seat*)malloc(sizeof(Seat));
		newSeat->seatNum = i;
		newSeat->name = name;
		newSeat->next = NULL;
		currentRow->seatList->next = newSeat;
		currentRow->seatList = newSeat;
	}
	
	printf("SUCCESS\n");
	return;
}

// lookup seat
void lookup(Row* rowList, int row, int seat) {
	// if row list is empty, return no one
	if (rowList->next == NULL) {
		printf("No one\n");
		return;
	}

	// if row exists, look for seat
	else {
		Row* currentRow = rowList->next;
		while (currentRow->next != NULL) {
			if (currentRow->rowNum == row) {
				Seat* currentSeat = currentRow->seatList;
				while (currentSeat->next != NULL) {
					if (currentSeat->seatNum == seat) {
						printf("%s\n", currentSeat->name);
						return;
					}
					currentSeat = currentSeat->next;
				}
			}
			currentRow = currentRow->next;
		}
	}

	// if seat is not taken, return no one
	printf("No one\n");
}

// quit program
void quit(Row* rowList) {
	// free memory
	free(rowList);
}

int main() {
	// create row list
	Row* rowList = (Row*)malloc(sizeof(Row));
	rowList->next = NULL;

	// read input
	char input[100];
	while (fgets(input, 100, stdin) != NULL) {
		// parse input
		char* command = strtok(input, " ");
		int row = atoi(strtok(NULL, " "));
		int start = atoi(strtok(NULL, " "));
		int end = atoi(strtok(NULL, " "));
		char* name = strtok(NULL, " ");

		// remove newline from name
		name[strlen(name) - 1] = '\0';

		// execute command
		if (strcmp(command, "BUY") == 0) {
			buy(rowList, row, start, end, name);
		}
		else if (strcmp(command, "LOOKUP") == 0) {
			lookup(rowList, row, start);
		}
		else if (strcmp(command, "QUIT") == 0) {
			quit(rowList);
			return 0;
		}
	}

	return 0;
}