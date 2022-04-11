#include "Q1.h"

/* Q1 - possibilities */

Array*** PossibleDigits(short sudokuBoard[][9])
{
	Array*** boardValidDigits;
	int row, col, logSize;
	Array* validDigitsOfPosition;

	boardValidDigits = (Array***)malloc(sizeof(Array**) * BOARD_ROWS);
	checkAllocation(boardValidDigits);

	for (col = 0; col < BOARD_ROWS; col++)
	{
		boardValidDigits[col] = (Array**)malloc(sizeof(Array*) * BOARD_COLS);
		checkAllocation(boardValidDigits[col]);
	}

	for (row = 0; row < BOARD_ROWS; row++)
		for (col = 0; col < BOARD_COLS; col++)
		{
			if (sudokuBoard[row][col] > 0 && sudokuBoard[row][col] <= 9)
				validDigitsOfPosition = NULL;
			else
			{
				validDigitsOfPosition = (Array*)malloc(sizeof(Array));
				checkAllocation(validDigitsOfPosition);

				updatePossibleDigits(validDigitsOfPosition, sudokuBoard, row, col);
			}
			boardValidDigits[row][col] = validDigitsOfPosition;
		}

	return boardValidDigits;
}

/*  update the possible digits of the cell in the array */
void updatePossibleDigits(Array* validDigitsOfPosition, short sudokuBoard[][BOARD_COLS], int row, int col)
{
	if (validDigitsOfPosition != NULL) 
	{
		int i;
		int countingArr[9] = { 0 };
		int countingArrLogicSize = countZeros(countingArr);
		short* arr;
		int index = 0;

		arr = (short*)malloc(sizeof(short) * countingArrLogicSize);
		checkAllocation(arr);

		updateCountingArr(countingArr, sudokuBoard, row, col);

		for (i = 0; i < 9; i++)
		{
			if (countingArr[i] == 0) /* if the digit i is valid */
			{
				arr[index] = i + 1;
				index++;
			}
		}

		validDigitsOfPosition->arr = arr;
		validDigitsOfPosition->size = index;
	}
}

/* The function count the number of zeros in the countingArr,
meaning - counting the number of valid digits of the cell */
int countZeros(int countingArr[])
{
	int count = 0;
	int i;

	for (i = 0; i < 9; i++)
	{
		if (countingArr[i] == 0)
			count++;
	}

	return count;
}

/* update the countingArr according row/col/box */
void updateCountingArr(int countingArr[], short sudokuBoard[][BOARD_COLS], int row, int col)
{
	int i, j;
	short  valueInCell;

	/* check the row */
	updateCountingArrByRow(countingArr, sudokuBoard, row);

	/* check the col */
	updateCountingArrByCol(countingArr, sudokuBoard, col);

	/* check the box */
	updateCountingArrByBox(countingArr, sudokuBoard, row, col);
}

/* update the CountingArr according to the row of the cell */
void updateCountingArrByRow(int countingArr[], short sudokuBoard[][BOARD_COLS], int row)
{
	int i;
	short valueInCell;

	for (i = 0; i < BOARD_ROWS; i++)
	{
		valueInCell = sudokuBoard[row][i];

		if (valueInCell != EMPTY_CELL)
			countingArr[valueInCell - 1] = 1;
	}
}

/* update the CountingArr according to the col of the cell */
void updateCountingArrByCol(int countingArr[], short sudokuBoard[][BOARD_COLS], int col)
{
	int i;
	short valueInCell;

	for (i = 0; i < BOARD_COLS; i++)
	{
		valueInCell = sudokuBoard[i][col];

		if (valueInCell != EMPTY_CELL)
			countingArr[valueInCell - 1] = 1;
	}
}

/* update the CountingArr according to the row of the cell */
void updateCountingArrByBox(int countingArr[], short sudokuBoard[][BOARD_COLS], int row, int col)
{
	int R, C, rowOfBox, colofBox;
	short valueInCell;


	R = (row / 3) * 3;
	C = (col / 3) * 3;

	for (rowOfBox = R; rowOfBox < R + 3; rowOfBox++)
	{
		for (colofBox = C; colofBox < C + 3; colofBox++)
		{
			valueInCell = sudokuBoard[rowOfBox][colofBox];
			if (valueInCell != EMPTY_CELL)
				countingArr[valueInCell - 1] = 1;
		}
	}
}

/* free Q1 */
void freeQ1(Array*** arr)
{
	int i, j, k;

	for (i = 0; i < BOARD_ROWS; i++)
	{
		for (j = 0; j < BOARD_COLS; j++)
		{
			if (arr[i][j] != NULL)
			{
				free(arr[i][j]->arr);    /*free every position in any cell*/
				free(arr[i][j]);             /* Free every struct in any cel */
			}
		}
		free(arr[i]);
	}
	free(arr);
}
