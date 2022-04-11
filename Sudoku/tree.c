#include "tree.h"

/* The function build a tree from an array */
Tree BuildTreeFromArray(LNodePlayer** arrOfPointers, int size)
{
	Tree newTree, leftTree, rightTree;
	int middle;
	newTree.root = NULL;

	if (size == 0)
		return newTree;

	newTree.root = (TreeNode*)malloc(sizeof(TreeNode));
	checkAllocation(newTree.root);

	if (size == 1)
		newTree.root = createNewTNode(&(arrOfPointers[0]), NULL, NULL);
	else
	{
		middle = size / 2;
		newTree.root->player = &(arrOfPointers[middle]); /*arr + middle*/ 

		if (arrOfPointers[middle / 2] != NULL)
		{
			leftTree = BuildTreeFromArray(arrOfPointers, middle);
			newTree.root->left = leftTree.root;
		}
		else
			newTree.root->left = NULL;

		if (arrOfPointers[(size + middle + 1) / 2] != NULL)
		{
			rightTree = BuildTreeFromArray(arrOfPointers + (middle + 1), size - middle-1);
			newTree.root->right = rightTree.root;
		}
		else
			newTree.root->right = NULL;
	}

	return newTree;
}

/* create new TNode */
TreeNode* createNewTNode(LNodePlayer** player, TreeNode* left, TreeNode* right)
{
	TreeNode* newTNode = (TreeNode*)malloc(sizeof(TreeNode));
	checkAllocation(newTNode);

	newTNode->player = player;
	newTNode->left = left;
	newTNode->right = right;

	return newTNode;
}

