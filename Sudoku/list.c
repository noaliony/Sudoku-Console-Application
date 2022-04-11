#include "list.h"

/* Create new node */
ListNode* createNode(int i, int j, ListNode* next)
{
	ListNode* node;

	node = (ListNode*)malloc(sizeof(ListNode));
	checkAllocation(node);

	node->point.x = i;
	node->point.y = j;
	node->next = NULL;

	return node;
}

LNodePlayer* createNodePlayers(Player player, LNodePlayer* next)
{
	LNodePlayer* nodePlayer;

	nodePlayer = (LNodePlayer*)malloc(sizeof(LNodePlayer));
	checkAllocation(nodePlayer);

	strcpy(nodePlayer->player.name, player.name);

	copyArr(nodePlayer->player.board, player.board);
	
	nodePlayer->player.possibilities = player.possibilities;

	nodePlayer->next = next; /* next == NULL */

	return nodePlayer;
}

/* Making a new list empty */
void makeEmptyList(LIST* lst)
{
	lst->head = lst->tail = NULL;
}

void makeEmptyListPlayers(LISTPlayer* lst)
{
	lst->head = lst->tail = NULL;
}

/* Insert node to end list */
void insertNodeToEndList(LIST* lst, ListNode* newTail)
{
	if (lst->head == NULL)
		lst->head = lst->tail = newTail;
	else
	{
		lst->tail->next = newTail;
		lst->tail = newTail;
	}
}

void insertNodePlayerToEndList(LISTPlayer* lst, LNodePlayer* newTail)
{
	if (lst->head == NULL)
		lst->head = lst->tail = newTail;
	else
	{
		lst->tail->next = newTail;
		lst->tail = newTail;
	}
}

/* Delete the next node from the list */
void deleteNode(ListNode* prev, LIST* lstCells)
{
	ListNode* next, * toDel;
	if (prev == NULL)
		toDel = lstCells->head;
	else
		toDel = prev->next;

	next = toDel->next;

	/* We want to delete the head of the list */
	if (lstCells->head == toDel)
	{
		lstCells->head = next;
	}
	/* We want to delete the tail of the list */
	else if (lstCells->tail == toDel)
	{
		lstCells->tail = prev;
	}
	/* We want to delete node from the middle of the list */
	else
	{
		prev->next = next;
	}

	free(toDel);
}

void deletePlayerNode(LNodePlayer* prev, LISTPlayer* lstplayers)
{
	
	LNodePlayer* next, * toDel;
	if (prev == NULL) /* We want to delete the head of the list */
	{
		toDel = lstplayers->head;
	}
	else
		toDel = prev->next;

	next = toDel->next;
	if (lstplayers->head == lstplayers->tail) /* if there is only one player */
	{
		lstplayers->head = lstplayers->tail = NULL;

	}
	else if (lstplayers->head == toDel) /* if we want to delete the head 
										(and there is more than one player) */
	{
		lstplayers->head = next;
	}
	else if (lstplayers->tail == toDel) /* We want to delete the tail of the list */
	{
		lstplayers->tail = prev;
		prev->next = NULL;
	}
	else /* We want to delete node from the middle of the list */
	{
		prev->next = next;
	}

	/* free(toDel->player.possibilities); */
	free(toDel);
}

void copyArr(short board1[][BOARD_COLS], short board2[][BOARD_COLS])
{
	int i, j;
	for (i = 0; i < BOARD_ROWS; i++)
	{
		for (j = 0; j < BOARD_COLS; j++)
		{
			board1[i][j] = board2[i][j];
		}
	}
}

void printListOfWinnersPlayers(LISTPlayer* lstPlayers)
{
	LNodePlayer* curr = lstPlayers->head;
	if (curr == NULL)
		printf("There are no winners.");
	else
	{
		printf("The list of the winners : \n\n");
		while (curr != NULL)
		{
			printf("Name of player : %s \n\n", curr->player.name);
			sudokoPrintBoard(curr->player.board);
			printf("\n"); /* space row */
			curr = curr->next;
		}
	}

}

LNodePlayer* lookForPlayerInlstPlayers(LISTPlayer* lstPlayers, char name[MAX_NAME])
{
	LNodePlayer* prevDel = NULL, *curr = lstPlayers->head;
	while (curr != NULL && (strcmp(curr->player.name, name) != 0))
	{
		prevDel = curr;
		curr = curr->next;
	}
	return prevDel;

}





