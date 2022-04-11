#include "freeAll.h"

void freeList(LIST* lst)
{
	ListNode* curr = lst->head, * next;
	while (curr)
	{
		next = curr->next;
		free(curr);
		curr = next;
	}
}

void freelstPlayers(LISTPlayer* lstPlayers)
{
	LNodePlayer* curr = lstPlayers->head, * next;
	while (curr)
	{
		next = curr->next;
		free(curr->player.possibilities);
		free(curr);
		curr = next;
	}
	free(lstPlayers);
}

void freeTree(Tree tr)
{
	freeTreeRec(tr.root);
}

void freeTreeRec(TreeNode* root)
{
	if (root == NULL)
		return;
	else
	{
		freeTreeRec(root->left);
		freeTreeRec(root->right);
		free(root);
	}
}







