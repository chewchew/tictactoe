#ifndef GAME
#define GAME

/* ===================================================
	 -- game.h -- 
	Contains functions for running a game of tictactoe.
   =================================================== 
*/

// data-structures
#include "data.h"

/* == print_board =========
	prints this board to terminal */
void print_board(Board board);

/* == make_move =========== 
	board - game board
	turn  - tile type of move*/
int make_move(Board board, int tile_type);

/* == game_end ============ 
	check if board is in terminating state.
	board - game board */
int game_end(Board board);

#endif
