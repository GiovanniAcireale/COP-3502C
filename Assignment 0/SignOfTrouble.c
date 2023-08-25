// Giovanni Acireale, 8/25/23, Assignment 0: Sign of Trouble

/*
* Story
	Your newest project is working on revitalizing the movie industry. There will be a lull in the
	upcoming movie productions due to all the strikes, and you want to support the area by
	renovating a local big box store into a theater.
	The first major change is to fix the signage around the store to reflect the new purpose of the
	space. The letters themselves of the old store are fine, and we still want a sign in the same
	places. The message of the sign will change, but to save costs we will reuse as many letters as
	possible.

*Problem
	Given the original message and the new message determine how many new letters will need to
	be purchased to create the new sign.
	
*Input
	The first line of input will contain a sequence of characters (uppercase letters and spaces)
	denoting the original message of the sign. The second line of input will contain a sequence of
	characters (uppercase letters and spaces) denoting the desired resulting message of the sign.
	You are guaranteed that each message will have at most 100,000 characters before the end of
	line characters.
	
*Output
	Output a single integer representing the number of letters that will need to be purchased.

Sample Input			Sample Output
ELECTRONICS
SNACKS AND DRINKS		10

SOFA SINK AND SUCH
REGRET CINEMAS			8

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// function makes all letters uppercase
void makeUpperCase(char* message, int messageLength) {
	int i;
	for (i = 0; i < messageLength; i++) {
		if (message[i] >= 'a' && message[i] <= 'z') {
			message[i] -= 32;
		}
	}
}

// function saves the original message
void saveOriginalMessage(char* originalMessage, int* originalMessageArray, int originalMessageLength) {
	int i;
	for (i = 0; i < originalMessageLength; i++) {
		if (originalMessage[i] >= 'A' && originalMessage[i] <= 'Z') {
			originalMessageArray[originalMessage[i] - 'A']++;
		}
	}
}

// function saves the new message
void saveNewMessage(char* newMessage, int* newMessageArray, int newMessageLength) {
	int i;
	for (i = 0; i < newMessageLength; i++) {
		if (newMessage[i] >= 'A' && newMessage[i] <= 'Z') {
			newMessageArray[newMessage[i] - 'A']++;
		}
	}
}

// function compares the original message and the new message and returns the amount of letters needed
int compareMessages(int* originalMessageArray, int* newMessageArray) {
	int i, lettersNeeded = 0;
	for (i = 0; i < 26; i++) {
		if (originalMessageArray[i] < newMessageArray[i]) {
			lettersNeeded += newMessageArray[i] - originalMessageArray[i];
		}
	}
	return lettersNeeded;
}

int main() {
	char originalMessage[100000], newMessage[100000];
	int originalMessageArray[26] = { 0 }, newMessageArray[26] = { 0 }, originalMessageLength, newMessageLength, lettersNeeded;

	// gets the original message and the new message
	fgets(originalMessage, 100000, stdin);
	fgets(newMessage, 100000, stdin);

	// gets the length of the original message and the new message
	originalMessageLength = strlen(originalMessage);
	newMessageLength = strlen(newMessage);

	// makes all letters uppercase
	makeUpperCase(originalMessage, originalMessageLength);
	makeUpperCase(newMessage, newMessageLength);

	// saves the original message and the new message
	saveOriginalMessage(originalMessage, originalMessageArray, originalMessageLength);
	saveNewMessage(newMessage, newMessageArray, newMessageLength);

	// compares the original message and the new message and returns the amount of letters needed
	lettersNeeded = compareMessages(originalMessageArray, newMessageArray);

	// prints the amount of letters needed
	printf("%d", lettersNeeded);

	return 0;
}