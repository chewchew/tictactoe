#include <stdlib.h>

#include "minimax.h"
#include "game.h"

// TESTING
#include <stdio.h>

// ========= LIST OPERATIONS =========
void list_add(int* size, Node** list, Node* node)
{
	list[*size] = node;
	(*size)++;
}

void list_remove(int* size, Node** list, int index)
{
	for (int i = index; i < *size - 1; i++)
		list[i] = list[i + 1];
	(*size)--;
}

// ========== SEARCH UTILS ===========
int get_buffer_size(Board board)
{
	int buffer = board.dimx * board.dimy;
	// factorial
	for (int i = buffer; i > 0; i--)
		buffer *= buffer;

	return buffer;
}

int get_possible_moves(Board board)
{
	int board_size = board.dimx * board.dimy;
	return board_size - board.used_spaces;
}

// ======== MEMORY MANAGEMENT ========
void free_tree(Tree* tree)
{
	Board board = tree->root->state;

	// init unvisited
	int unvisited_size = 0;
	Node* unvisited[get_buffer_size(board)];

	// add root to unvisited
	Node* root = tree->root;
	list_add(&unvisited_size, unvisited, root);

	while (unvisited_size > 0)
	{
		Node* current = unvisited[0];

		for (int i = 0; i < current->n_children; i++)
			list_add(&unvisited_size, unvisited, current->children[i]);

		if (current->move)
			free(current->move);
		if (current->children)
			free(current->children);
		if (current)
			free(current);

		list_remove(&unvisited_size, unvisited, 0);
	}

	free(tree);
}

// =========== init_tree ============
Tree* init_tree(Board board)
{
	Tree* tree = (Tree*) malloc(sizeof(Tree));

	Node* root = (Node*) malloc(sizeof(Node));
	root->state  = board; 
	root->move   = 0;
	root->value  = 0;
	root->parent = 0;
	tree->root = root;

	return tree;
	
}
// ========= create_children =========
void create_children(Node* node, Board board)
{
	int possible_moves = get_possible_moves(board);
	node->children = (Node**) malloc(sizeof(Node) * possible_moves);

	int moves_found = 0;
	for (int x = 0; x < board.dimx; x++)
	{
		for (int y = 0; y < board.dimy; y++)
		{
			if (board.tiles[x][y].type == NONE)
			{
				Node* child = (Node*) malloc(sizeof(Node));

				child->parent = node;
				child->move = (int*) malloc(sizeof(int) * 2);
				(child->move)[0] = x;
				(child->move)[1] = y;

				(node->children)[moves_found] = child;
				moves_found++;
			}
		}
	}
}

// ============== RUN ================
int* run(Board board, int player)
{
	Tree* tree = init_tree(board);

	int unvisited_size = 0;
	Node* unvisited[get_buffer_size(board)];

	list_add(&unvisited_size, unvisited, tree->root);

	while (unvisited_size > 0)
	{
		Node* current = unvisited[0];

		create_children(current,board);
		
	}

	return 0;
}

/*===========================================
  ================= TESTING =================
  ===========================================
*/
void print_title(char* title)
{
	printf("=== %s ===\n",title);
}

void print_result(char* msg, char* expected, char* result, int success)
{
	printf("Test for (%s) was",msg);
	if (!success)
		printf(" not");
	printf(" successful!\n");

	if (expected != 0 || result != 0)
	{
		printf("Expected : %s ",expected);
		printf("Got : %s\n",result);
	}
}

Node** init_test(char* title, int buffer)
{
	print_title(title);

	Node** list = (Node**) malloc(sizeof(Node*) * (buffer));

	return list;
}

Node* alloc_node()
{
	Node* node = (Node*) malloc(sizeof(Node));
	return node;
}

// free allocated memory for list and its pointer (not their data)
void free_mem(Node** list, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (list[i])
			free(list[i]);
	}
	free(list);
}

void test_add()
{
	// init
	int real_size = 0;
	int size = 0;
	int buffer = 100;

	Node** list = init_test("add",buffer);

	Node* n1 = alloc_node();
	Node* n2 = alloc_node();
	
	// add n1 and n2
	list_add(&size,list,n1);
	real_size++;
	list_add(&size,list,n2);
	real_size++;

	// result size
	char expected[2];
	char result[2];
	sprintf(expected,"%d",real_size);
	sprintf(result,"%d",size);
	print_result("size has changed", expected, result, size == real_size);

	// result add for n1 and n2
	print_result("node 1 was added",0,0, list[0] == n1);
	print_result("node 2 was added",0,0, list[1] == n2);

	// free allocated memory
	free_mem(list,real_size);
}

void test_remove()
{
	// init
	int real_size = 0;
	int size = 0;
	int buffer = 100;
	Node** list = init_test("remove",buffer);

	// allocate memory for nodes
	Node* n1 = alloc_node();
	Node* n2 = alloc_node();
	Node* n3 = alloc_node();

	// add nodes to list
	list_add(&size,list,n1);
	real_size++;
	list_add(&size,list,n2);
	real_size++;
	list_add(&size,list,n3);
	real_size++;

	// remove node with index 1
	list_remove(&size,list,1);
	real_size--;

	// check size
	char expected[2];
	char result[2];
	sprintf(expected,"%d",real_size);
	sprintf(result,"%d",size);
	print_result("size has changed", expected, result, size == real_size);

	// check if removed properly
	int n2_not_in_list = 1;
	for (int i = 0; i < buffer; i++)
	{
		if(list[i] == n2)
			n2_not_in_list = 0;
	}
	int remove_ok = list[0] == n1 &&
					list[1] == n3 &&
					n2_not_in_list;
	print_result("node was removed",0,0, remove_ok);

	free_mem(list,real_size);
}
