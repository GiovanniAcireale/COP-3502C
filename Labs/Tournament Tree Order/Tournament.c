// Giovanni Acireale, Lab, 10/17/23

/*
Create a single elimination bracket tournament of N competitors.
	- Each round consist of one game between two competitors.
	- There will always be N - 1 games because one player will be eliminated each game.
	- At the beginning of the tournament there will be N - 1 game areas lined up in a row.
	- There is exactly one player spot between each adjacent pair of game areas.
	- There are two additional player spots before the first game area and after the second game area.
	- Each player will take one of theses spots.
	- No spot can be occupied by more than one player.
	- In each round a single game area will be used for a game and the player closest on the left will play against the player closest on the right.
	- There can be only one winner, no draws.
	- After which the losing player will leave and the winning player will move to the next game area.

Visual aid:

	Player 1 | Area 1 | Player 2 | Area 2 | Player 3 | Area 3 | Player 4 | Area 4 | Player 5


*/