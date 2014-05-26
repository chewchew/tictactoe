#include "game.h"

#include <stdio.h>

// ======= HELPER FUNCTIONS FOR print_board =======
void print_roof(Board board)
{
	printf("  ");
	for (int x = 0; x < board.dimx; x++)
		printf("*----");
	printf("*\n");
}

void print_row(Board board, int x)
{
	printf("%i ",x);
	for (int y = 0; y < board.dimy; y++)
	{
		printf("| ");
		switch(board.tiles[x][y].type)
		{
		case CIRCLE:
			printf("o");
			break;
		case CROSS:
			printf("x");
			break;
		case NONE:
			printf(" ");
			break;
		}
		printf("  ");
	}
	printf("|\n");
}
// === END HELPER ===

void print_board(Board board)
{
	for (int x = 0; x < board.dimx; x++)
		printf("    %i",x);
	printf("\n");
	
	print_roof(board);
	
	for (int x = 0; x < board.dimx; x++)
	{
		print_row(board, x);
		print_roof(board);
	}
}

// ======= HELPER FUNCTIONS FOR make_move =========
int get_input(char* msg, int min, int max)
{
	int input = max + 1;
	printf(msg);
	while (input >= max || input <= min)
	{
		scanf("%d", &input);
		if (input >= max || input <= min)
			printf("Bad input! Try again..\n");
	}
	return input;
}
// === END HELPER ===

int make_move(Board board, int tile_type)
{
	printf("Whats your move?\n");
	
	int row = get_input("row : ", -1, board.dimx);	
	int column = get_input("column : ", -1, board.dimy);
	
	if (board.tiles[row][column].type != NONE)
		return 0;
	board.tiles[row][column].type = tile_type;
	return 1;
}

// ======= HELPER FUNCTIONS FOR game_end ==========
int check_row(Board board, int x)
{
	int tile_type = board.tiles[x][0].type;
	if (tile_type == NONE)
		return 0;
	for (int i = 1; i < board.dimx; i++)
	{
		if (tile_type != board.tiles[x][i].type)
			return 0;
	}
	return 1;
}

int check_column(Board board, int y)
{
	int tile_type = board.tiles[0][y].type;
	if (tile_type == NONE)
		return 0;
	for (int i = 0; i < board.dimy; i++)
	{
		if (tile_type != board.tiles[0][i].type)
			return 0;
	}
	return 1;
}

int check_diagonals(Board board)
{
	int diag1 = 1;
	int tile_type = board.tiles[0][0].type;
	if (tile_type == NONE)
		diag1 = 0;
	else
	{
		for (int i = 0, j = 0; i < board.dimx || j < board.dimy; i++, j++)
		{
			if (tile_type != board.tiles[i][j].type)
				diag1 = 0;
		}
	}
		
	int diag2 = 1;
	tile_type = board.tiles[2][0].type;
	if (tile_type == NONE)
		diag2 = 0;
	else
		{
		for (int i = 2, j = 0; i >= 0 || j < board.dimy; i--, j++)
		{
			if (tile_type != board.tiles[i][j].type)
				diag2 = 0;
		}
	}
	
	return diag1 + diag2;
}

// === END HELPER ===

int game_end(Board board)
{
	for (int x = 0; x < board.dimx; x++)
	{
		if (check_row(board,x))
			return 1;
	}
	for (int y = 0; y < board.dimy; y++)
	{
		if (check_column(board,y))
			return 1;
	}
	if (check_diagonals(board))
		return 1;
		
	if (board.used_spaces == board.dimx * board.dimy)
		return 2;	
		
	return 0;
}
