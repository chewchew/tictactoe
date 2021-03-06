#include <stdio.h>
#include <stdlib.h>

#include "game.h"

void refresh_terminal(Board board, int turn)
{
	system("clear");
	printf("Turn : "); 
	if (turn == CIRCLE)
		printf("Circle\n");
	else if (turn == CROSS)
		printf("Cross\n");
	print_board(board);
}

int main()
{
	// init players
	int players[2];
	players[0] = CIRCLE;
	players[1] = CROSS;
	
	// init 3x3 board
	int dimx = 3;
	int dimy = 3;
	Tile** tiles = malloc(sizeof(Tile*) * dimx);
	for (int x = 0; x < dimx; x++)
	{
		tiles[x] = malloc(sizeof(Tile) * dimy);
		for (int y = 0; y < dimy; y++)
		{
			Tile tile;
			tile.x = x;
			tile.y = y;
			tile.type = NONE;
			tiles[x][y] = tile;
		}
	}
	Board board;
	board.dimx        = dimx;
	board.dimy        = dimy;
	board.used_spaces = 0;
	board.tiles       = tiles;
	
	// setup game-variables
	int turn = 0;
	int move_ok = 1;
	
	// run game
	while(!game_end(board))
	{
		refresh_terminal(board,turn);
		if (! move_ok)
			printf("{{ Space already occupied! }}");
		printf("\n");
		move_ok = make_move(board,turn);
		if (move_ok)
		{
			board.used_spaces++;
			turn = (turn + 1) % 2;
		}
	}
	
	// invert turn since it was changed to other before ending loop
	turn = (turn + 1) % 2;
	
	refresh_terminal(board, -1);
	char* win_msg = "The winner is : ";
	if (game_end(board) == 2)
		printf("Draw!\n");
	else if (turn == CIRCLE)
		printf("%sCircle!\n",win_msg);
	else
		printf("%sCross!\n",win_msg);

	// free space
	for (int x = 0; x < dimx; x++)
	{
		free(tiles[x]);
	}
	free(tiles);
}

