
#include <stdio.h>
#include <stdlib.h>

#define MAXOPTIONS 7
#define MAXLENGTH 15
#define COMBOLENGTH 3

char options[MAXOPTIONS][MAXLENGTH] = {
	"apples",
	"bananas",
	"grapes",
	"oranges",
	"grapefruit",
	"kiwi",
	"tomatoes"
};

int combo[COMBOLENGTH];

int count = 0;

void makeCombos(int idx, int numUsed) {
	if(numUsed == COMBOLENGTH) {
		count++;
		printf("%d: ", count);
		for(int i = 0; i < COMBOLENGTH; i++) {
			printf("%s ", options[combo[i]]);
		}
		printf("\n");

		return;
	}

	if (idx == MAXOPTIONS){
		return;
	}

	// add current option to combo
	combo[numUsed] = idx;
	makeCombos(idx + 1, numUsed + 1);

	// ignore current option
	combo[numUsed] = -1;
	makeCombos(idx + 1, numUsed);

}

int main() {
	for (int i = 0; i < COMBOLENGTH; i++) {
		combo[i] = -1;
	}

	makeCombos(0, 0);

	return 0;
}
