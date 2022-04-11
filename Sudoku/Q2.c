
#include "Q2.h"

/* Q2 - one stage */

int OneStage(short board[][BOARD_COLS], Array*** possibilities, int* x, int* y)
{
	int i, j, min = 9;
	int data;
	int statusBoard = 1; /* initalize to somethhing different from FINISH_FAILURE (-1) */
	bool changedPossibilities = true, ifFailure = false, fullBoard; /* changedPossibilities => we just puted digits in places with 1 option,
																	so we want tokeep run to check if the digit that we just puted made
																	other cell Options to be 1 option only.
																	ifFailure = FINISH_FAILURE
																	fullBoard = FINISH_SUCCESS */

	while (changedPossibilities == true && ifFailure == false && statusBoard != FINISH_FAILURE)
	{ 
		changedPossibilities = false;
		fullBoard = true;
		for (i = 0; i < BOARD_ROWS; i++)
			for (j = 0; j < BOARD_COLS; j++)
			{
				if (possibilities[i][j] == NULL && board[i][j] == EMPTY_CELL)
					ifFailure = true; /* illegal board */

				if (possibilities[i][j] != NULL) /* if we want to place digit in the cell */
				{
					data = possibilities[i][j]->arr[0];

					if (possibilities[i][j]->size == 1)
					{    /* if there is only one digit avilibale */
						board[i][j] = data;
						updatePossibilitiesArr(possibilities, i, j, data, &statusBoard, board); /* free inside */
						changedPossibilities = true;
					}

				}
			}
	}

	for (i = 0; i < BOARD_ROWS; i++)
		for (j = 0; j < BOARD_COLS; j++)
		{
			if (possibilities[i][j] != NULL)
			{
				if (possibilities[i][j]->size < min)
				{
					min = possibilities[i][j]->size;
					*x = i;
					*y = j;
				}
				if (board[i][j] == EMPTY_CELL) /* if we did'nt place yet a digit in the cell */
					fullBoard = false;
			}

		}

	if (statusBoard == FINISH_FAILURE || ifFailure == true) /* The board is not full (not leagel) */
	{
		x = NULL;
		y = NULL;
		return FINISH_FAILURE;
	}
	else if (fullBoard == true) /* The board is full */
	{
		x = NULL;
		y = NULL;
		return FINISH_SUCCESS;
	}
	else /* The board is not full */
	{
		return NOT_FINISH;
		/* the x , y are already the minimum */
	}
}

/* update the possibilities and free*/
void updatePossibilitiesArr(Array*** possibilities, int i, int j, short data, int* statusBoard, short board[][BOARD_COLS])
{
	updateRow(i, j, possibilities, data, statusBoard, board);
	if (*statusBoard != FINISH_FAILURE)
		updateCol(i, j, possibilities, data, statusBoard, board);
	if (*statusBoard != FINISH_FAILURE)
		updateBox(i, j, possibilities, data, statusBoard, board);

	free(possibilities[i][j]->arr);
	free(possibilities[i][j]);

	possibilities[i][j] = NULL;
}

/* The function update the ARRAY of every cell in the row,
meaning - delete the data from the array of the digits*/
void updateRow(int row, int col, Array*** possibilities, int data, int* statusBoard, short board[][BOARD_COLS])
{
	int i, j, k, currSize;
	bool flag = false;

	for (i = 0; i < BOARD_COLS && *statusBoard != FINISH_FAILURE; i++) /* run over the row */
	{
		if (possibilities[row][i] != NULL && i != col) /* we don't want to check the  cases :
													   # there is already digit int the cell.
													   # the cell with the 1 posibility that we are working at it at this function.*/
		{
			if (board[row][i] == data)
				*statusBoard = FINISH_FAILURE;
			currSize = possibilities[row][i]->size;
			for (j = 0; j < currSize && flag == false && *statusBoard != FINISH_FAILURE; j++) /* run over the Array of every cell at the row */
			{


				if (possibilities[row][i]->arr[j] == data) /* if one of the options of the digits is the data */
				{
					swap(&(possibilities[row][i]->arr[j]), &(possibilities[row][i]->arr[currSize - 1])); /* swap the 'bad' digit to the end of the array */

					(possibilities[row][i]->size)--;

					if (possibilities[row][i]->size == 0) /* Ilegal board (duplications) */
						*statusBoard = FINISH_FAILURE;
					else
					{
						possibilities[row][i]->arr = (short*)realloc(possibilities[row][i]->arr, sizeof(short) * possibilities[row][i]->size);
						checkAllocation(possibilities[row][i]->arr);
						flag = true;
					}
				}
			}
			flag = false;
		}
	}
}

/* The function update the ARRAY of every cell in the col,
meaning - delete the data from the array of the digits */
void updateCol(int row, int col, Array*** possibilities, int data, int* statusBoard, short board[][BOARD_COLS])
{
	int i, j, k, currSize;;
	bool flag = false;

	for (i = 0; i < BOARD_ROWS && *statusBoard != FINISH_FAILURE; i++) /* run over the col */
	{
		if (possibilities[i][col] != NULL && i != row) /* we don't want to check the  cases :
													   # there is already digit int the cell.
													   # the cell with the 1 posibility that we are working at it at this function.*/
		{
			if (board[i][col] == data)
				*statusBoard = FINISH_FAILURE;
			currSize = possibilities[i][col]->size;
			for (j = 0; j < currSize && flag == false && *statusBoard != FINISH_FAILURE; j++) /* run over the Array of every cell at the col */
			{
				if (possibilities[i][col]->arr[j] == data) /* if one of the options of the digits is the data */
				{
					swap(&(possibilities[i][col]->arr[j]), &(possibilities[i][col]->arr[currSize - 1])); /* swap the 'bad' digit to the end of the array */

					(possibilities[i][col]->size)--;

					if (possibilities[i][col]->size == 0) /* Ilegal board (duplications) */
						*statusBoard = FINISH_FAILURE;
					else
					{
						possibilities[i][col]->arr = (short*)realloc(possibilities[i][col]->arr, sizeof(short) * possibilities[i][col]->size);
						checkAllocation(possibilities[i][col]->arr);
						flag = true;
					}
				}
			}
			flag = false;
		}
	}

}

/* The function update the ARRAY of every cell in the box,
meaning - delete the data from the array of the digits */
void updateBox(int row, int col, Array*** possibilities, int data, int* statusBoard, short board[][BOARD_COLS])
{
	int R = (row / 3) * 3, C = (col / 3) * 3, rowOfBox, colOfBox;
	int i, k;
	bool flag = false;
	int currSize;

	for (rowOfBox = R; rowOfBox < R + 3 && flag == false && *statusBoard != FINISH_FAILURE; rowOfBox++)
	{
		for (colOfBox = C; colOfBox < C + 3 && flag == false && *statusBoard != FINISH_FAILURE; colOfBox++)
		{ /* run over every cell in the box */
			if (possibilities[rowOfBox][colOfBox] != NULL && (rowOfBox != row || colOfBox != col)) /* we don't want to check the  cases :
																								# there is already digit int the cell.
																								# the cell with the 1 posibility that
																								  we are working at it at this function.*/
			{
				if (board[rowOfBox][colOfBox] == data)
					*statusBoard = FINISH_FAILURE;
				currSize = possibilities[rowOfBox][colOfBox]->size;
				for (i = 0; i < possibilities[rowOfBox][colOfBox]->size && flag == false && *statusBoard != FINISH_FAILURE; i++) /* run over every digit of the options in arr */
				{
					if (possibilities[rowOfBox][colOfBox]->arr[i] == data) /* if one of the options of the digits is the data */
					{
						swap(&(possibilities[rowOfBox][colOfBox]->arr[i]), &(possibilities[rowOfBox][colOfBox]->arr[currSize - 1])); /* swap the 'bad' digit to the end of the array */

						(possibilities[rowOfBox][colOfBox]->size)--;

						if (possibilities[rowOfBox][colOfBox]->size == 0) /* Ilegal board (duplications) */
							*statusBoard = FINISH_FAILURE;
						else
						{
							possibilities[rowOfBox][colOfBox]->arr = (short*)realloc(possibilities[rowOfBox][colOfBox]->arr, sizeof(short) * possibilities[rowOfBox][colOfBox]->size);
							checkAllocation(possibilities[rowOfBox][colOfBox]->arr);
							flag = true;
						}
					}
				}
				flag = false;
			}
		}
	}

}

/* swap 2 short values (from the arr at ARRAY) */
void swap(short* sh1, short* sh2)
{
	short temp;

	temp = *sh1;
	*sh1 = *sh2;
	*sh2 = temp;
}