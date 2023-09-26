//
/*

ideat structure

d1 <= d2 <= d3 <= d4 <= ... <= dn

while q is not empty
	get current location from q

	dq(q)
	try all adjacent locations
		if location is valid
			if location is destination
				return
			else
				mark location as visited
				aq(q, location)

---------------------------------------------

Stacks (ADT)

LIFO - Last In First Out

ADT - Abstract Data Type

only have access to the "top" of the stack

support removal from the top of the stack

for addition you add to the top of the stack

i.e 

top() // returns the top of the stack

	arguement stack
	returns element at the top of the stack

pop() // removes the top of the stack

	arguement stack
	returns nothing

push() // adds to the top of the stack

	arguement stack, value
	returns nothing

Implementations:

	1. Array
	2. Linked List

---------------------------------------------

Linked List Implementation

top()
	returns head's value

push(value)
	insert head(value)

pop()
	remove head

---------------------------------------------

Usage of Stacks

1. program stack

	call a function
	push onto stack
	return from function
	remove most recent function from stack

2. parsing

	what is parsing?

		reading a string of characters and determining if it is valid

		1. parenthesis matching
		2. infix to postfix conversion
		3. postfix evaluation

	post fix
		1. push operations onto stack
		2. when you see an operator pop two operands off the stack
		3. perform the operation on the two operands
		4. push the result onto the stack

		2 algorithms:
			1. convert infix to postfix
			2. evaluate postfix

			which is easier to implement? evaluate postfix
				because you don't have to worry about order of operations
				in order to convert infix to postfix you need to know order of operations

---------------------------------------------

Post-Fix expression evaluation

	1. read the expression from left to right (loop)
	2. if you see an operand push it onto the stack
	3. if you see an operator pop two operands off the stack
		a = top(); pop();
		b = top(); pop();
		res->eval(a, b, operator);
		push(res);
			top() is the answer
	4. perform the operation on the two operands
	5. push the result onto the stack



*/