#ifndef freeAll

#define freeAll
#include "structs.h"
#include "list.h"
#include "tree.h"

void freeList(LIST* lst);
void freelstPlayers(LISTPlayer* lstPlayers);
void freeTree(Tree tr);
void freeTreeRec(TreeNode* root);

#endif 

