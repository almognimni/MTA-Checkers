#ifndef PROJECT_TREE_H
#define PROJECT_TREE_H

#define LEFT 0
#define RIGHT 1

#include "board.h"
#include "stdbool.h"

/* Data structs */
typedef struct _SingleSourceMovesTreeNode
{
    Board board;
    checkersPos *pos;
    unsigned short total_captures_so_far;
    struct _SingleSourceMovesTreeNode *next_moves[2];

}SingleSourceMovesTreeNode;

typedef struct _SingleSourceMovesTree
{
    SingleSourceMovesTreeNode *source;
}SingleSourceMovesTree;

/*Functions*/
SingleSourceMovesTreeNode* createNewTNode(Board board, int row, int col, unsigned short *total_captures_so_far);
int isBorT(Board board, int row, int col);
SingleSourceMovesTreeNode* buildTreeHelper(Board board, int row, int col, int sourceSide, unsigned short* totalCaptures);
void printTreeHelper(SingleSourceMovesTreeNode *root);
void printTreeInorder(SingleSourceMovesTree tr);
bool isInRange(int row, int col);
SingleSourceMovesTreeNode* test(Board board, int row, int col, int sourceSide, unsigned short* totalCaptures);
//isNodeParamNeeded
#endif

