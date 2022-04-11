#ifndef structs

#define structs
#include "utils.h"

typedef struct _Cell
{
	int x; /* row */
	int y; /* col */
} CELL;

typedef struct _Array
{
	short* arr;
	unsigned short size;
} Array;

typedef struct _Player
{
	char name[100];
	short board[BOARD_ROWS][BOARD_COLS];
	Array*** possibilities;
} Player;




#endif 
