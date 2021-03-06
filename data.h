#ifndef DATA
#define DATA

/* ===================================================
	 -- data.h -- 
	Contains data-structures for the game tictactoe.
   =================================================== 
*/
	
// == Tile types ==========
#define CROSS  0
#define CIRCLE 1
#define NONE   2

/* == Tile =================
	x    - x position on board
	y    - y position on board
	type - type of this tile (CROSS/CIRCLE/NONE) */
typedef struct
{
	int x;
	int y;
	int type;	
} Tile;

/* == Board ================
	tiles - two-dimensional array of tiles representing board */
typedef struct
{
	int dimx;
	int dimy;
	int used_spaces;
	Tile** tiles;
} Board;

#endif
