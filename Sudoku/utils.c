#include "utils.h"

void checkAllocation(void* p)
{
	if (p == NULL)
	{
		printf("Allocation Falied");
		exit(1);
	}
}

void sudokoPrintBoard(short int board[][BOARD_COLS])
{/* prints curr board values to UI */
	short int row, col;
	printf("  |");
	for (col = 0; col < BOARD_COLS; col++)
	{
		printf("%2d", col);/*board cols number */
		if (col % 3 == 2 && col != 8)/*every 3 rows besides last row */
			printf("|");
	}
	printf("\n");
	printf("-----------------------");
	printf("\n");
	for (row = 0; row < BOARD_ROWS; row++)
	{
		printf(" %d|", row);/* board rows number */
		for (col = 0; col < BOARD_COLS; col++)
		{
			(board[row][col] != EMPTY_CELL) ? printf("%2d", board[row][col]) : printf("  ");
			if (col % 3 == 2 && col != 8)/*every 3 rows besides last row */
				printf("|");
		}
		if (row % 3 == 2)/* every 3 rows */  
		{
			printf("\n");
			printf("-----------------------");
		}
		printf("\n");
	}
	printf("\n");
}
