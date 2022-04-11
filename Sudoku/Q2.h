#ifndef Q2_H
#define Q2_H

#include "structs.h"
#include "utils.h"
#include <stdbool.h>
#include "Q1.h"

int OneStage(short board[][BOARD_COLS], Array*** possibilities, int* x, int* y);
void updatePossibilitiesArr(Array*** possibilities, int i, int j, short data, int* statusBoard, short board[][BOARD_COLS]);
void updateRow(int row, int col, Array*** possibilities, int data, int* statusBoard, short board[][BOARD_COLS]);
void updateCol(int row, int col, Array*** possibilities, int data, int* statusBoard, short board[][BOARD_COLS]);
void updateBox(int row, int col, Array*** possibilities, int data, int* statusBoard, short board[][BOARD_COLS]);
void swap(short* sh1, short* sh2);

#endif
