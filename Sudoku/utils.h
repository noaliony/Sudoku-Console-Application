#define  _CRT_SECURE_NO_WARNINGS
#ifndef utils
#define utils

#include <stdlib.h>
#include <stdio.h>
#define BOARD_ROWS 9
#define BOARD_COLS 9
#define EMPTY_CELL -1
#define NOT_FINISH 0 
#define FINISH_SUCCESS 1 
#define FINISH_FAILURE -1 
#define FAIL -1 
#define FILLED 1 
#define MAX_NAME 100

void checkAllocation(void* p);
void sudokoPrintBoard(short board[][BOARD_COLS]);

#endif 
