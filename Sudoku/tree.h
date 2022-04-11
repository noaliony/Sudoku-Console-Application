#ifndef treeh

#define treeh
#include "structs.h"
#include "utils.h"
#include "list.h"

typedef struct tnode 
{
	LNodePlayer** player; /* type of point to cell in array */
	struct tnode* left;
	struct tnode* right;
}TreeNode;

typedef struct tree 
{
	TreeNode* root;
}Tree;

Tree BuildTreeFromArray(LNodePlayer** arrOfPointers, int size);
TreeNode* createNewTNode(LNodePlayer** player, TreeNode* left, TreeNode* right);

#endif 



