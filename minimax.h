#ifndef MINIMAX
#define MINIMAX

#include "data.h"

// ========= Node ============
typedef struct Node Node;
struct Node
{
	Board state;

	int* move;

	int value;

	Node* parent;

	int n_children;
	Node** children;
};

// ========= Tree ============
typedef struct Tree Tree;
struct Tree
{
	Node* root;
};

/* =========== run ===========
	find current best move, 
	returns an array with best coordinates, e.g: (1,0)

	board  - the current state of the game
	player - the player whos turn it is */
int* run(Board board, int player);

// =============== TESTING ===============
void test_add();
void test_remove();

#endif