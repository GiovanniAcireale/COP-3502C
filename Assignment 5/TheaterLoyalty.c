// Giovanni Acireale, Assignment 5, 11/13/23
/*
Background Story

Our theater is now experimenting with pie shaped projectors (turned out to be a big fail!)
Instead, they are going to copy the Universal Cinema Foundation and start a rewards program.
Each guest gets 1 loyalty point for each dollar they spend at the theater. Over time, guests may
gain loyalty points, use loyalty points to redeem prizes or query the number of loyalty points
they have. On occasion, a guest may get very upset at the theater (maybe they showed the Taylor
Swift movie one too many times), and request to be removed from the loyalty program. One
strange request the theater wants the program to handle is a query of how many users have
names that come alphabetically before a particular user.
Since the theater knows you are learning about binary search trees in class, they would like for
you to implement this functionality via a binary search tree of nodes, where the nodes are
compared via the name of the customer stored in the node, in alphabetical order.

Problem

Write a program that reads in input corresponding to various changes and queries to the theater's
loyalty program and prints out corresponding messages for each of the input commands. Here is
an informal list of each of the possible commands in the input:
(1) Add Loyalty Points to a particular customer.
(2) Subtract Loyalty Points from a particular customer.
(3) Delete a particular customer.
(4) Search for a particular customer in the binary search tree. If the customer is found, report
both their number of loyalty points and their depth in the tree (distance from the root in # of links
to follow.)
(5) Count the number of customers whose names come alphabetically before a particular
customer.
At the very end of the input, your program should store pointers to each struct storing customer
data and sort that data by loyalty points, from highest to lowest, breaking ties alphabetically. (For
two customers with the same number of loyalty points, the one whose name comes first
alphabetically should be listed first.) This data should be sorted via either Merge Sort or Quick
Sort.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct for the customer
typedef struct customer {
	char *name;
	int points;
	struct customer *left;
	struct customer *right;
} customer;

// Function prototypes
customer *addCustomer(customer *root, char *name, int points);
customer *deleteCustomer(customer *root, char *name);
customer *findCustomer(customer *root, char *name);
customer *findMin(customer *root);
int countCustomers(customer *root, char *name);
void printCustomers(customer *root);
void freeCustomers(customer *root);

// Main function
int main() {
	// Initialize variables
	int points, depth, count;
	char name[100];
	char command[100];
	customer *root = NULL, *temp = NULL;

	/*
	Input
	The first line of input contains a single positive integer: n (n ? 300,000), the number of
	commands to process.
	The next n lines will each contain a single command. Note: The commands will be such that
	the resulting binary search tree will never exceed a height of 100.
	Here is the format of each of the possible input lines:
	Command 1
	add <name> <points>
	<name> will be a lowercase alphabetic string with no more than 19 characters.
	<points> will be a positive integer less than or equal to 100.
	Command 2
	sub <name> <points>
	<name> will be a lowercase alphabetic string with no more than 19 characters.
	<points> will be a positive integer less than or equal to 100.
	Note: if a customer has fewer points than is specified in this command to subtract, then just
	subtract the total number of points they have instead.
	Command 3
	del <name>
	<name> will be a lowercase alphabetic string with no more than 19 characters.
	Delete the customer with the name <name> from the binary search tree. No action is taken if
	the customer isn't in the tree to begin with.
	Command 4
	search <name>
	<name> will be a lowercase alphabetic string with no more than 19 characters.
	This will search for the customer with the name <name> and report both the number of loyalty
	points the customer has and the depth of the node in the tree storing that customer, if the
	customer is in the tree.
	Command 5
	count_smaller <name>
	<name> will be a lowercase alphabetic string with no more than 19 characters.
	This will calculate the number of names in the binary search tree that come alphabetically before
	<name>.
	
	Output
	For each input command, output a single line as described below:
	Command 1
	Print out a single line with the format:
	<name> <points>
	where <name> is the name of the customer who added points and <points> is the new total
	number of points they have. Note: If the customer is not in the binary search tree, then create a
	new node for them initialized to <points> number of points. If the customer is already in the
	binary search tree, just add <points> number of points to their current total.
	Command 2
	If the customer is NOT in the tree, print out a single line with the format:
	<name> not found
	If the customer is in the tree, print out a single line with the format:
	<name> <points>
	where <name> is the name of the customer who subtracted points and <points> is the new
	total number of points they have. Note: if the points to be subtracted was greater than the points
	they previously had, then after the operation, they will have 0 points left.
	Command 3
	If the customer in question wasn't found in the binary search tree, output the following line:
	<name> not found
	If the name is found, output a line with the following format:
	<name> deleted
	where <name> is the name of the customer being deleted. (Of course, delete the node storing
	that customer from the tree!) If you are deleting a node with two children, please replace it
	with the maximum node in the left subtree. This is to ensure there is one right answer for
	each test case.
	Command 4
	If the customer in question wasn't found in the binary search tree, output the following line:
	<name> not found
	If the name is found, output a line with the following format:
	<name> <points> <depth>
	where <name> is the name of the customer being searched, <points> is the number of
	loyalty points they currently have and <depth> is the distance of the node the customer in
	question was found in from the root node of the tree.
	Command 5
	For this command, just print a single integer on a line by itself representing the number of names
	in the binary search tree that come before <name>, alphabetically. (Note: Because we require a
	run time of O(h), where h is the height of the tree, this is likely the most challenging command to
	process. The size field will be necessary in the node struct to make this determination in O(h)
	time.)
	After all commands in the input have been processed, create an array to store pointers to each
	struct storing customer data. Then, sort that array by customer loyalty points from highest to
	lowest, breaking ties by the names in alphabetical order as previously described. Finally, print
	out one line per customer in this sorted order with the format:
	<name> <points>
	where <name> is the name of the customer and <points> is the number of loyalty points
	they have at the end of the set of input commands.
	*/

	// Scan the number of commands
	scanf("%d", &count);

	// For each command
	for (int i = 0; i < count; i++) {
		// Scan the command
		scanf("%s", command);
		// If the command is add
		if (strcmp(command, "add") == 0) {
			// Scan the name and points
			scanf("%s %d", name, &points);
			// Add the customer
			root = addCustomer(root, name, points);
			// Print the customer
			printf("%s %d\n", name, points);
			// If the command is sub
		}
		else if (strcmp(command, "sub") == 0) {
			// Scan the name and points
			scanf("%s %d", name, &points);
			// Find the customer
			temp = findCustomer(root, name);
			// If the customer is NULL
			if (temp == NULL) {
				// Print the customer not found
				printf("%s not found\n", name);
				// If the customer is not NULL
			}
			else {
				// Subtract the points
				temp->points -= points;
				// If the points are less than 0
				if (temp->points < 0) {
					// Set the points to 0
					temp->points = 0;
				}
				// Print the customer
				printf("%s %d\n", name, temp->points);
			}
			// If the command is del
		}
		else if (strcmp(command, "del") == 0) {
			// Scan the name
			scanf("%s", name);
			// Delete the customer
			root = deleteCustomer(root, name);
			// Print the customer
			printf("%s deleted\n", name);
			// If the command is search
		}
		else if (strcmp(command, "search") == 0) {
			// Scan the name
			scanf("%s", name);
			// Find the customer
			temp = findCustomer(root, name);
			// If the customer is NULL
			if (temp == NULL) {
				// Print the customer not found
				printf("%s not found\n", name);
				// If the customer is not NULL
			}
			else {
				// Count the customers
				depth = countCustomers(root, name);
				// Print the customer
				printf("%s %d %d\n", name, temp->points, depth);
			}
			// If the command is count_smaller
		}
		else if (strcmp(command, "count_smaller") == 0) {
			// Scan the name
			scanf("%s", name);
			// Count the customers
			count = countCustomers(root, name);
			// Print the count
			printf("%d\n", count);
		}
	}

	// Print the customers
	printCustomers(root);

	// Free the customers
	freeCustomers(root);

	// Return 0
	return 0;
}

// Function to add a customer
customer *addCustomer(customer *root, char *name, int points) {
	// If the root is NULL
	if (root == NULL) {
		// Allocate memory for the customer
		root = malloc(sizeof(customer));
		// Allocate memory for the name
		root->name = malloc(sizeof(char) * (strlen(name) + 1));
		// Copy the name
		strcpy(root->name, name);
		// Set the points
		root->points = points;
		// Set the left and right to NULL
		root->left = NULL;
		root->right = NULL;
		// Return the root
		return root;
	}
	// If the name is less than the root's name
	if (strcmp(name, root->name) < 0) {
		// Add the customer to the left
		root->left = addCustomer(root->left, name, points);
	// If the name is greater than the root's name
	} else if (strcmp(name, root->name) > 0) {
		// Add the customer to the right
		root->right = addCustomer(root->right, name, points);
	// If the name is equal to the root's name
	} else {
		// Add the points
		root->points += points;
	}
	// Return the root
	return root;
}

// Function to delete a customer
customer *deleteCustomer(customer *root, char *name) {
	// If the root is NULL
	if (root == NULL) {
		// Return NULL
		return NULL;
	}
	// If the name is less than the root's name
	if (strcmp(name, root->name) < 0) {
		// Delete the customer from the left
		root->left = deleteCustomer(root->left, name);
	// If the name is greater than the root's name
	} else if (strcmp(name, root->name) > 0) {
		// Delete the customer from the right
		root->right = deleteCustomer(root->right, name);
	// If the name is equal to the root's name
	} else {
		// If the root has no children
		if (root->left == NULL && root->right == NULL) {
			// Free the name
			free(root->name);
			// Free the root
			free(root);
			// Set the root to NULL
			root = NULL;
		// If the root has a left child
		} else if (root->left != NULL && root->right == NULL) {
			// Free the name
			free(root->name);
			// Free the root
			free(root);
			// Set the root to the left child
			root = root->left;
		// If the root has a right child
		} else if (root->left == NULL && root->right != NULL) {
			// Free the name
			free(root->name);
			// Free the root
			free(root);
			// Set the root to the right child
			root = root->right;
		// If the root has two children
		} else {
			// Find the minimum node in the right subtree
			customer *temp = findMin(root->right);
			// Free the name
			free(root->name);
			// Copy the name
			root->name = malloc(sizeof(char) * (strlen(temp->name) + 1));
			strcpy(root->name, temp->name);
			// Set the points
			root->points = temp->points;
			// Delete the minimum node in the right subtree
			root->right = deleteCustomer(root->right, temp->name);
		}
	}
	// Return the root
	return root;
}

// Function to find a customer
customer *findCustomer(customer *root, char *name) {
	// If the root is NULL
	if (root == NULL) {
		// Return NULL
		return NULL;
	}
	// If the name is less than the root's name
	if (strcmp(name, root->name) < 0) {
		// Find the customer in the left subtree
		return findCustomer(root->left, name);
	// If the name is greater than the root's name
	} else if (strcmp(name, root->name) > 0) {
		// Find the customer in the right subtree
		return findCustomer(root->right, name);
	// If the name is equal to the root's name
	} else {
		// Return the root
		return root;
	}
}

// Function to find the minimum node in the right subtree
customer *findMin(customer *root) {
	// If the root is NULL
	if (root == NULL) {
		// Return NULL
		return NULL;
	}
	// If the root has no left child
	if (root->left == NULL) {
		// Return the root
		return root;
	}
	// Find the minimum node in the left subtree
	return findMin(root->left);
}

// Function to count the number of customers before a customer
int countCustomers(customer *root, char *name) {
	// If the root is NULL
	if (root == NULL) {
		// Return 0
		return 0;
	}
	// If the name is less than the root's name
	if (strcmp(name, root->name) < 0) {
		// Count the customers in the left subtree
		return countCustomers(root->left, name);
	// If the name is greater than the root's name
	} else if (strcmp(name, root->name) > 0) {
		// Count the customers in the left subtree, the root, and the right subtree
		return 1 + countCustomers(root->left, name) + countCustomers(root->right, name);
	// If the name is equal to the root's name
	} else {
		// Count the customers in the left subtree
		return countCustomers(root->left, name);
	}
}

// Function to print the customers
void printCustomers(customer *root) {
	// If the root is NULL
	if (root == NULL) {
		// Return
		return;
	}
	// Print the left subtree
	printCustomers(root->left);
	// Print the name and points
	printf("%s %d\n", root->name, root->points);
	// Print the right subtree
	printCustomers(root->right);
}

// Function to free the customers
void freeCustomers(customer *root) {
	// If the root is NULL
	if (root == NULL) {
		// Return
		return;
	}
	// Free the left subtree
	freeCustomers(root->left);
	// Free the right subtree
	freeCustomers(root->right);
	// Free the name
	free(root->name);
	// Free the root
	free(root);
}
