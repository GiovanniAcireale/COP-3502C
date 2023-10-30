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
	int numberOfPeople;
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
		if (angle < 0) angle += 360; // convert to positive angle (0 - 360)

		// input data into the group
		groups[i]->angle = angle;
		groups[i]->numberOfPeople = groupSize;
	}

	return groups;
}

// Functions:

// Sort all groups by the angle
// effectively sort the groups using merge or quick sort
void merge(struct Group** arr, int left, int mid, int right) {
	int i, j, k;
	int n1 = mid - left + 1;
	int n2 = right - mid;

	// Create temporary arrays
	struct Group** L = (struct Group**)malloc(n1 * sizeof(struct Group*));
	struct Group** R = (struct Group**)malloc(n2 * sizeof(struct Group*));

	// Copy data to temporary arrays L[] and R[]
	for (i = 0; i < n1; i++) {
		L[i] = arr[left + i];
	}
	for (j = 0; j < n2; j++) {
		R[j] = arr[mid + 1 + j];
	}

	// Merge the temporary arrays back into arr[left..right]
	i = 0;
	j = 0;
	k = left;

	while (i < n1 && j < n2) {
		if (L[i]->angle <= R[j]->angle) {
			arr[k] = L[i];
			i++;
		}
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	// Copy the remaining elements of L[], if any
	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}

	// Copy the remaining elements of R[], if any
	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}

	free(L);
	free(R);
}

// Main Merge Sort function
void mergeSort(struct Group** arr, int left, int right) {
	if (left < right) {
		int mid = left + (right - left) / 2;

		// Sort first and second halves
		mergeSort(arr, left, mid);
		mergeSort(arr, mid + 1, right);

		// Merge the sorted halves
		merge(arr, left, mid, right);
	}
}

// find the maximum angle that can be used such that no one is in the
// projection cone
double maxAngle(struct Group** groups, int numberOfGroups, int initialAngle) {
	// Sort the array of groups by angle (if not sorted already)
	//mergeSort(groups, 0, numberOfGroups - 1);

	double maxGap = 0.0;

	// Calculate the gap between the first and last group to handle wrap-around
	double wrapAroundGap = groups[0]->angle + (360.0 - groups[numberOfGroups - 1]->angle);

	for (int i = 1; i < numberOfGroups; i++) {
		double gap = groups[i]->angle - groups[i - 1]->angle;
		if (gap > maxGap) {
			maxGap = gap;
		}
	}

	// Calculate the gap between the last group and the initial angle
	double gapToInitial = initialAngle - groups[numberOfGroups - 1]->angle;

	// Check if either of the two gaps is larger than the maximum gap found
	if (wrapAroundGap > maxGap) {
		maxGap = wrapAroundGap;
	}

	if (gapToInitial > maxGap) {
		maxGap = gapToInitial;
	}

	return maxGap;
}

// You should use a 2 pointer sweep to effectively find the minimum
// number of people in the projection cone. You can sweep through 
// the groups in order of their angle with the first pointer.
// for each pointer (exclusive) you can bump up the last pointer if
// the group should be in the circle sector. When the front is 
// updated the sum should be decreased, and when the back is 
// updated the sum should be increased.
// find the minimum number of people in the projection cone
int minPeopleInCone(struct Group** groups, int numberOfGroups, int initialAngle) {
	// Sort the array by angle using Merge Sort
	//mergeSort(groups, 0, numberOfGroups - 1);

	// Initialize two pointers
	int front = 0; // Front pointer
	int back = 0;  // Back pointer
	int sum = groups[0]->numberOfPeople; // Initialize sum with the first group's size

	int minPeople = sum; // Initialize the minimum people with the initial sum

	while (front < numberOfGroups) {
		// Check if the gap is less than or equal to the initial angle
		double gap = groups[front]->angle - groups[back]->angle;
		if (gap <= initialAngle) {
			// Move the front pointer to include more groups
			front++;
			if (front < numberOfGroups) {
				sum += groups[front]->numberOfPeople;
			}
		}
		else {
			// Move the back pointer to decrease the sum
			sum -= groups[back]->numberOfPeople;
			back++;
			// Check if the back pointer caught up to the front
			if (back == front && front < numberOfGroups) {
				// Move the front pointer to include more groups
				front++;
				if (front < numberOfGroups) {
					sum += groups[front]->numberOfPeople;
				}
			}
		}

		// Update the minimum people in the cone
		if (sum < minPeople) {
			minPeople = sum;
		}
	}

	return minPeople;
}



// main function
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
	/*
	// Test group creation:
	printf("\nTEST GROUP CREATION:\n");
	for (int i = 0; i < numberOfGroups; i++) {
		printf("Group %d: angle: %f, size: %d\n", groups[i]->id, groups[i]->angle, groups[i]->numberOfPeople);
	} 
	printf("TEST GROUP CREATION END\n\n");
	// PASSED
	*/
	// Sort the array by angle using Merge Sort
	mergeSort(groups, 0, numberOfGroups - 1);
	/*
	// Test group sort by angle
	printf("\nTEST GROUP SORT:\n");
	printf("Sorted Array by Angle:\n");
	for (int i = 0; i < numberOfGroups; i++) {
		printf("Group %d: angle: %.2lf, size: %d\n",
			groups[i]->id, groups[i]->angle, groups[i]->numberOfPeople);
	}
	printf("TEST GROUP SORT END\n\n");
	// PASSED
	*/
	// Test max angle
	double max_gap = maxAngle(groups, numberOfGroups, initialAngle);
	//printf("Maximum Angle Gap: %.4lf degrees\n", max_gap);
	// PASSED

	// Test min peeps
	int min_people = minPeopleInCone(groups, numberOfGroups, initialAngle);
	if (max_gap > initialAngle) {
		min_people = 0;
		//printf("Minimum Number of People in Projection Cone: %d\n", min_people);
	}
	else {
		//printf("Minimum Number of People in Projection Cone: %d\n", min_people);
	}
	// PASSED
	
	// OUTPUT
	printf("\n%d\n", min_people);
	printf("%.4lf\n", max_gap);

	
	// free allocated memory
	for (int i = 0; i < numberOfGroups; i++) {
		free(groups[i]);
	}
	free(groups);

	return 0;
}


