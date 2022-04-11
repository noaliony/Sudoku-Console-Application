#include "Q3.h"

/* Q3 - fill the board */

int FillBoard(short board[][9], Array*** possibilities)
{
	int status;
	int x, y;
	int i, j;
	int statusBoard = 1; /* initalize to somethhing different from FINISH_FAILURE (-1) */
	short  chosenDigit;
	Array** countArr;

	status = OneStage(board, possibilities, &x, &y); /* call to Q2 */

	while (status == NOT_FINISH)
	{
		printf("please choose one of the following digits to the cell (row - %d, col - %d): \n", x,y);
		for (i = 0; i < possibilities[x][y]->size; i++)
			printf("%d  ", possibilities[x][y]->arr[i]);
		printf("\n");
		scanf("%hd", &chosenDigit);

		board[x][y] = chosenDigit;

		updatePossibilitiesArr(possibilities, x, y, chosenDigit, &statusBoard, board); /* free inside */

		status = OneStage(board, possibilities, &x, &y); /* call to Q2 */
	}

	if (status == FINISH_SUCCESS)
		return FILLED;
	else if (status == FINISH_FAILURE || statusBoard == FINISH_FAILURE)
		return FAIL;
}
