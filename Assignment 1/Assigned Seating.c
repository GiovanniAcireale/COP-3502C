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

