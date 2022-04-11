#ifndef listh

#define listh
#include "structs.h"
#include "utils.h"
#include <string.h>

typedef struct _ListNode
{
	CELL point;
	struct _ListNode* next;
}ListNode;

typedef struct _List
{
	struct _ListNode* head;
	struct _ListNode* tail;
}LIST;

typedef struct _LNodePlayer
{
	Player player;
	struct LNodePlayer* next;
}LNodePlayer;

typedef struct _ListPlayer
{
	LNodePlayer* head;
	LNodePlayer* tail;
}LISTPlayer;

ListNode* createNode(int i, int j, ListNode* next);
void makeEmptyList(LIST* lst);
void insertNodeToEndList(LIST* lst, ListNode* newTail);
void deleteNode(ListNode* prev, LIST* lstCells);
void insertNodePlayerToEndList(LISTPlayer* lst, LNodePlayer* newTail);
void makeEmptyListPlayers(LISTPlayer* lst);
LNodePlayer* createNodePlayers(Player player, LNodePlayer* next);
void deletePlayerNode(LNodePlayer* prev, LISTPlayer* lstplayers);
void copyArr(short board1[][BOARD_COLS], short board2[][BOARD_COLS]);
void printListOfWinnersPlayers(LISTPlayer* lstPlayers);
LNodePlayer* lookForPlayerInlstPlayers(LISTPlayer* lstPlayers, char name[MAX_NAME]);

#endif 
