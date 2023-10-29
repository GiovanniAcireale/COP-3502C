// Giovanni Acireale, Assignment 4, 10/17/23

/*
Story:

	Your movie theater is trying out a new projector. The projection will be in the center of a circular
	room and will project a movie onto a part of the wall. The screen will project a sector of light at
	some angle width which comes at some default value, but can be updated based on a setting.
	The projector can be rotated such that the projection starts at any angle in the room.
	However you have several locations that groups of people have decided to stand at in the room.
	These groups of people are relatively small compared to the distance they are from the
	projector and can be treated as points with 0 radius. Although the projection won’t be disturbed
	by our infinitely thin customers, the light emitted from the projector does have some potential to
	damage organic entities.

You want to answer 2 main questions:

	1. What is the least number of people that will be in the projection assuming we choose the
	   optimal projection location assuming the angle of projection is at the default setting?

	2. What is the largest possible angle of projection that can be used such that no one is in
	   the will stand in the projection?

Problem:

	Given the locations and number of people in the groups, find the least number of people that are
	required to be in some sector defined by a center and an angle. Additionally, determine the
	largest angle that can be used such that no one is in the projection.

Input:

	Input starts with a line containing 2 integers, N and A, (1 ? N ? 500,000; 1 ? A ? 359)
	representing the number of people standing in the room and the angle in degrees at which the
	screen projector initially projects.

	The following N lines will each contain 3 space separated integers, x, y, and s, (0 ? |x|, |y| ?
	1,000,000; 1 ? s ? 1,000), representing x and y coordinates respectively of the location of a
	group and the number of people in that given group. Assume that the projector will be located at
	location (0, 0).

	Note: since the customers are so small multiple customers could stand at the same location.

Output:

	The output should consist of 2 lines. The first line will contain an integer representing the
	minimum number of people that would be in the projection. The second line will contain a
	floating point value that specifies the maximum angle in degrees that can be used such that no
	person will be in the projection rounded to 4 digits after the decimal. It’s guaranteed that the first
	answer would remain the change.

Sample Input:	|	Sample Output:
------------------------------------
	4 91		|	3
	0 5 3		|	90.0000
	10 0 5		|
	-4 0 12		|
	0 -3 4		|
------------------------------------
	3 181		|	0
	1 1 8		|	251.5651
	-2 1 5		|
	2 10 10		|
------------------------------------


*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265

// Group struct: the most critical information is the angle from the
// x-axis the groups lies at and the number of people in the groups.
typedef struct Group {
	int id;
	double angle;
	int size;
} Group;

// an array of groups
struct Group** createAndInitializeGroups(int size) {
	struct Group** groups = malloc(size * sizeof(struct Group*));

	if (groups == NULL) {
		printf("Memory allocation failed.\n");
		return NULL;
	}

	for (int i = 0; i < size; i++) {
		groups[i] = (struct Group*)malloc(sizeof(struct Group));
		groups[i]->id = i + 1;

		int x, y, groupSize;
		scanf("%d %d %d", &x, &y, &groupSize);
		if (x < -1000000 || x > 1000000 || y < -1000000 || y > 1000000 || size < 1 || size > 1000) {
			printf("Invalid input\n");
			return 0;
		}

		// calculate the angle from origin
		// You can compute the angle most accurately using the atan2 function
		// from the math header. This function takes in a y and x coordinate
		// and returns the angle from the y-axis. You can then convert this
		// angle to degrees by multiplying by 180 and dividing by PI.
		double angle = atan2(x,y) * 180 / PI;

		// input data into the group
		groups[i]->angle = angle;
		groups[i]->size = groupSize;
	}

	return groups;
}


// You should use a 2 pointer sweep to effectively find the minimum
// number of people in the projection cone. You can sweep through 
// the groups in order of their angle with the first pointer.
// for each pointer (exclusive) you can bump up the last pointer if
// the group should be in the circle sector. When the front is 
// updated the sum should be decreased, and when the back is 
// updated the sum should be increased.

// Functions:

// Sort all groups by the angle
// effectively sort the groups using merge or quick sort
void sortGroups(Group *groups, int size) {
	// using merge sort


}

// find the minimum number of people in the projection cone
int minPeople(Group *groups, int size, int angle) {
	// TODO
	return 0;
}

// find the maximum angle that can be used such that no one is in the
// projection cone
double maxAngle(Group *groups, int size) {
	// TODO
	return 0;
}






int main() {

	int numberOfGroups, initialAngle;
	
	// input will be in the form of: numberOfGroups initialAngle
	// where 1 <= numberOfGroups <= 500,000
	// And 1 <= initialAngle <= 359
	scanf("%d %d", &numberOfGroups, &initialAngle);
	if (numberOfGroups < 1 || numberOfGroups > 500000 || initialAngle < 1 || initialAngle > 359) {
		printf("Invalid input\n");
		return 1;
	}

	struct Group** groups = createAndInitializeGroups(numberOfGroups);

	if (groups == NULL) {
		printf("Memory allocation failed.\n");
		return 1;
	}

	// Test group creation:
	printf("\nTEST GROUP CREATION:\n");
	for (int i = 0; i < numberOfGroups; i++) {
		printf("Group %d: angle: %f, size: %d\n", groups[i]->id, groups[i]->angle, groups[i]->size);
	} 
	printf("TEST GROUP CREATION END\n\n");
	// PASSED

	// sort groups by angle
	sortGroups(groups, numberOfGroups);
	// ^ WIP ^ 10/28

	// free allocated memory
	for (int i = 0; i < numberOfGroups; i++) {
		free(groups[i]);
	}
	free(groups);

	return 0;
}


