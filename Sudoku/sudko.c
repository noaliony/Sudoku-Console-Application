#include "sudoku.h"

/* Init random board */
void initializeSudokuBoard(short board[][BOARD_COLS])
{
	int i, j, randIndex, row, col;
	int N, K;
	int sizeOfList = BOARD_ROWS * BOARD_COLS;
	LIST lstCells;
	ListNode* node, * curr, * prev = NULL;
	bool checkDigit = true;
	Array* opations = (Array*)malloc(sizeof(Array));
	checkAllocation(opations);

	makeEmptyList(&lstCells);

	for (i = 0; i < BOARD_ROWS; i++)
		for (j = 0; j < BOARD_COLS; j++)
		{
			node = createNode(i, j, NULL);

			if (i == 0 && j == 0)
				lstCells.head = lstCells.tail = node;
			if (i == 8 && j == 8)
				lstCells.tail = node;

			insertNodeToEndList(&lstCells, node);
		}

	/* Init all board to EMPTY_CELL (-1) */
	initBoard(board);

	N = 1 + rand() % 20; /* 1-20 */

	/* N - How many cells will start with digit */
	for (i = 0; i < N; i++)
	{
		K = 1 + rand() % sizeOfList; /* 1-81 */
		curr = lstCells.head;

		/* Curr will be the cell number (k) in the list  */
		for (j = 1; j < K-1; j++)
		{
			prev = curr;
			curr = curr->next;
		}

		row = curr->point.x;
		col = curr->point.y;
		if (board[row][col] != EMPTY_CELL)
			i--;

		else
		{
			/* we randomize digit to the node (K) for cell (x,y of K) in the board */
			
			updatePossibleDigits(opations, board, row, col);

			randIndex = rand() % opations->size;
			board[row][col] = (opations->arr)[randIndex];
			free(opations->arr);
			deleteNode(prev, &lstCells);
			(sizeOfList)--;
		}

	}
	free(opations);
	freeList(&lstCells);
}

/* Init the board to EMPTY_CELL (-1) */
void initBoard(short board[][BOARD_COLS])
{
	int i, j;

	for (i = 0; i < BOARD_ROWS; i++)
		for (j = 0; j < BOARD_COLS; j++)
		{
			board[i][j] = EMPTY_CELL;
		}

}

/* start program */
void startProgram()
{
	LISTPlayer* lstPlayers, *lstWinners;
	LNodePlayer** arrOfPointers;
	Tree treePlayers;
	
	int X, n, i;
	int* countCellsArr;
	char ch;
	printf("Please enter the number of activity players\n");
	scanf("%d", &X);
	ch = getchar(); /* for \n */
	if (X > 0)
	{
		lstPlayers = getNamesPlayers(X);

		arrOfPointers = createPointArrToNodes(lstPlayers, X);
		
		mergeSort(arrOfPointers, X);

		n = updateTheSizeOfArr(&arrOfPointers, X);
		treePlayers = BuildTreeFromArray(arrOfPointers, n);

		lstWinners = (LISTPlayer*)malloc(sizeof(LISTPlayer));
		checkAllocation(lstWinners);
		makeEmptyListPlayers(lstWinners);

		while (lstPlayers->head != NULL)
		{
			updatelstPlayers(treePlayers.root, lstPlayers, lstWinners);
		}

		printListOfWinnersPlayers(lstWinners);
		if (lstWinners->head != NULL)
			freelstPlayers(lstWinners);
		/* lstPlayers must be empty list right now */
		free(lstPlayers);

		freeTree(treePlayers);
		free(arrOfPointers);
	}
	printf("\nGoodBye :)\n");
}


/* update the list of players */
void updatelstPlayers(TreeNode* root, LISTPlayer* lstPlayers, LISTPlayer* lstWinners)
{
	int status, x, y;
	LNodePlayer* newWin;
	LNodePlayer* prevDel = NULL;
	if (root == NULL)
		return;
	else if (root->player == NULL && root->left == NULL && root->right == NULL)
		return;
	else
	{
		if (root->left != NULL)
		{
			updatelstPlayers(root->left, lstPlayers, lstWinners);
		}

		if (root->player != NULL)
		{   
			/* Here we take care of the root */
			status = OneStage((*(root->player))->player.board, (*(root->player))->player.possibilities, &x, &y);
			if (status == FINISH_FAILURE)
			{
				/* delete node from lstPlayers and
				null in pointer from the tree */
				printf("the player %s had duplication \n", (*(root->player))->player.name);
				prevDel = lookForPlayerInlstPlayers(lstPlayers, (*(root->player))->player.name);
				deletePlayerNode(prevDel, lstPlayers);
				root->player = NULL;
			}
			else if (status == FINISH_SUCCESS)
			{
				/* move player from lstPlayers to lstWinners
				and null in pointer from the tree */
				newWin = createNodePlayers((*(root->player))->player, NULL);
				insertNodePlayerToEndList(lstWinners, newWin);
				prevDel = lookForPlayerInlstPlayers(lstPlayers, (*(root->player))->player.name);
				deletePlayerNode(prevDel, lstPlayers);
				root->player = NULL;

			}
			else /* NOT_FINISHED */
			{
				chosenDigitAndUpdate((*(root->player))->player.possibilities, (*(root->player))->player.board, x, y, status, (*(root->player))->player.name);
			}
		}

		if (root->right != NULL)
		{
			updatelstPlayers(root->right, lstPlayers, lstWinners);
		}
	}
}

/* choose the digit and update the board and the possibilities */
void chosenDigitAndUpdate(Array*** possibilities, short board[][BOARD_COLS], int x, int y, int statusBoard, char name[MAX_NAME])
{
	int i;
	short chosenDigit;
	int chosenDigitIsGood = 0;
	sudokoPrintBoard(board);
	printf("%s, please choose one of the following digits to the cell (row - %d, col - %d): \n", name, x, y);
	for (i = 0; i < possibilities[x][y]->size; i++)
		printf("%d  ", possibilities[x][y]->arr[i]);
	printf("\n");
	scanf("%hd", &chosenDigit);

	/* check valid digit */
	 while (chosenDigitIsGood == 0)
	{
		for (i = 0; i < possibilities[x][y]->size; i++)
		{
			if (chosenDigit == possibilities[x][y]->arr[i])
				chosenDigitIsGood = 1;
		}
		if (chosenDigitIsGood == 0)
		{
			printf("%s, please choose a valid number:\n", name);
			scanf("%hd", &chosenDigit);
		}
	}

	board[x][y] = chosenDigit;

	updatePossibilitiesArr(possibilities, x, y, chosenDigit, &statusBoard, board); /* free inside */
}

/* Create pointer to list activity players and get their names */
LISTPlayer* getNamesPlayers(int X)
{
	int i;
	Player player;
	LNodePlayer* curr;
	LISTPlayer* lstPlayers = (LISTPlayer*)malloc(sizeof(LISTPlayer));
	checkAllocation(lstPlayers);
	makeEmptyListPlayers(lstPlayers);

	for (i = 0; i < X; i++)
	{
		player = createPlayer();
		curr = createNodePlayers(player, NULL);
		insertNodePlayerToEndList(lstPlayers, curr);
	}

	return lstPlayers;
}

/* Create single player */
Player createPlayer()
{
	Player player;
	int index = 0;
	char ch;

	printf("Please enter name to player\n");
	ch = getchar();

	while (index == 0 && (ch == '\0' || ch == '\n'))
	{
		printf("Input is invalidity\nPlease enter valid name to player\n");
		ch = getchar();
	}
	while (ch != '\0' && ch != '\n' && index < MAX_NAME - 1)
	{
		
		player.name[index] = ch;
		index++;
		ch = getchar();
	}
	player.name[index] = '\0';

	initializeSudokuBoard(player.board);

	player.possibilities = PossibleDigits(player.board);

	return player;
}

/* Create arr which every cell is pointer to node in lstPlayers */
LNodePlayer** createPointArrToNodes(LISTPlayer* lstPlayers, int X)
{
	LNodePlayer** arrOfPointers;
	LNodePlayer* curr;

	arrOfPointers = (LNodePlayer**)malloc(sizeof(LNodePlayer*) * X); /* create arr */
	checkAllocation(arrOfPointers);

	curr = lstPlayers->head;

	for (int i = 0; i < X; i++)
	{
		arrOfPointers[i] = (LNodePlayer*)malloc(sizeof(LNodePlayer)); /* create any pointer to node*/
		checkAllocation(arrOfPointers[i]);
		arrOfPointers[i] = curr;
		curr = curr->next;
	}

	return arrOfPointers;
}

/* count the number of full cells of the player */
int countFullCellsOfPlayer(short boardPlayer[][BOARD_COLS])
{
	int i, j;
	int count = 0;

	for (i = 0; i < BOARD_ROWS; i++)
	{
		for (j = 0; j < BOARD_COLS; j++)
		{
			if (boardPlayer[i][j] != EMPTY_CELL)
				count++;
		}
	}

	return count;
}

/* merge sort of list of players */
void mergeSort(LNodePlayer** arrOfPointers, int size)
{
	LNodePlayer** tmpArr = NULL;
	int i;
	if (size <= 1)
		return;

	mergeSort(arrOfPointers, size / 2);
	mergeSort(arrOfPointers + size / 2 , size - size / 2);
	tmpArr = merge(arrOfPointers, size / 2, arrOfPointers + size / 2, size - size / 2);
	checkAllocation(tmpArr);

	for (i = 0; i < size; i++)
		arrOfPointers[i] = tmpArr[i];
	free(tmpArr);
	
}

/* helper to the merge sort of list of players */
LNodePlayer** merge(LNodePlayer** a1, int size1, LNodePlayer** a2, int size2)
{
	int numofFullCells1, numofFullCells2, lexicograpy;
	int ind1, ind2, resInd;
	LNodePlayer** res = (LNodePlayer**)malloc((size1 + size2) * sizeof(LNodePlayer*));

	if (res)
	{
		ind1 = ind2 = resInd = 0;

		while ((ind1 < size1) && (ind2 < size2)) 
		{
			numofFullCells1 = countFullCellsOfPlayer(a1[ind1]->player.board);
			numofFullCells2 = countFullCellsOfPlayer(a2[ind2]->player.board);

			if (numofFullCells1 < numofFullCells2)
			{
				res[resInd] = a1[ind1];
				ind1++;
			}
			else if(numofFullCells1 > numofFullCells2)
			{
				res[resInd] = a2[ind2];
				ind2++;
			}
			else 
			{
				lexicograpy = strcmp(a1[ind1]->player.name, a2[ind2]->player.name);

				if (lexicograpy < 0)
				{
					res[resInd] = a1[ind1];
					ind1++;
				}
				else
				{
					res[resInd] = a2[ind2];
					ind2++;
				}
			}
			resInd++;
		}

		while (ind1 < size1) 
		{
			res[resInd] = a1[ind1];
			ind1++;
			resInd++;
		}
		while (ind2 < size2) 
		{
			res[resInd] = a2[ind2];
			ind2++;
			resInd++;
		}
	}
	return res;
}

/* print the name and the board of the player */
void printPlayer(Player player)
{
	printf("%s\n", player.name);
	sudokoPrintBoard(player.board);
}

/* calculate n according to X */
double calcNByX(int X)
{
	double n;
	double power;

	power = (log10(X+1)) / (log10(2));
	n = pow(2, power) - 1;
	
	return n;
}

/* udate the size of arr according to n */
int updateTheSizeOfArr(LNodePlayer*** arrOfPointers, int X)
{
	int n, i;

	n = calcNByX(X);
	*arrOfPointers = (LNodePlayer**)realloc(*arrOfPointers, n * sizeof(LNodePlayer*));
	checkAllocation(*arrOfPointers);
	for (i = X; i < n; i++)
		(*arrOfPointers)[i] = NULL;

	return n;
}

/* print the tree */
void printTree(Tree tree, int n, LNodePlayer** arrOfPointers)
{
	printTreeRec(tree.root, n, arrOfPointers);
}

/* print the tree - helper */
void printTreeRec(TreeNode* root, int n, LNodePlayer** arrOfPointers)
{
	if (root == NULL)
		return;
	else
	{
		printTreeRec(root->left, n, arrOfPointers);
		if (root->player != NULL && (*(root->player)) != NULL)
			printPlayer((*(root->player))->player);
		printTreeRec(root->right, n, arrOfPointers);

	}
}