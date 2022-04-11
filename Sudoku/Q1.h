#ifndef Q1_H
#define Q1_H
#include <stdlib.h>
#include "structs.h"
#include "utils.h"

Array*** PossibleDigits(short sudokuBoard[][BOARD_COLS]);
void updatePossibleDigits(Array* validDigitsOfPosition, short sudokuBoard[][BOARD_COLS], int row, int col);
int countZeros(int countingArr[]);
void updateCountingArr(int countingArr[], short board[][BOARD_COLS], int row, int col);
void updateCountingArrByRow(int countingArr[], short board[][BOARD_COLS], int row);
void updateCountingArrByCol(int countingArr[], short board[][BOARD_COLS], int col);
void updateCountingArrByBox(int countingArr[], short board[][BOARD_COLS], int row, int col);
void freeQ1(Array*** arr);

#endif