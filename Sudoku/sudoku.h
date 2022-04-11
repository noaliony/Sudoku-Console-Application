#ifndef  sudko

#define sudko
#include "structs.h"
#include "utils.h"
#include <stdbool.h>
#include "list.h"
#include "Q1.h"
#include <math.h>
#include "tree.h"
#include "Q2.h"
#include "freeAll.h"

void initializeSudokuBoard(short board[][BOARD_COLS]);
void initBoard(short board[][BOARD_COLS]);
void startProgram();
Player createPlayer();
LNodePlayer** createPointArrToNodes(LISTPlayer* lstPlayers, int X);
LISTPlayer* getNamesPlayers(int X);
int countFullCellsOfPlayer(short boardPlayer[][BOARD_COLS]);
void mergeSort(LNodePlayer** arrOfPointers, int size);
LNodePlayer** merge(LNodePlayer** a1, int size1, LNodePlayer** a2, int size2);
void printPlayer(Player player);
double calcNByX(int X);
int updateTheSizeOfArr(LNodePlayer*** arrOfPointers, int X);
void chosenDigitAndUpdate(Array*** possibilities, short board[][BOARD_COLS], int x, int y, int statusBoard, char name[MAX_NAME]);
void updatelstPlayers(TreeNode* root, LISTPlayer* lstPlayers, LISTPlayer* lstWinners);
void printTree(Tree tree, int n, LNodePlayer** arrOfPointers);
void printTreeRec(TreeNode* root, int n, LNodePlayer** arrOfPointers);

#endif 


