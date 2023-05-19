#ifndef PROJECT_TREE_H
#define PROJECT_TREE_H

#define LEFT 0
#define RIGHT 1

#include "board.h"


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


SingleSourceMovesTree *FindSingleSourceMoves(Board board, checkersPos *src);
void buildTreeHelper(Board *board, SingleSourceMovesTreeNode *node, int row, int col, int is_capturing);
SingleSourceMovesTreeNode* createNewTNode(Board *board, int row, int col);
#endif

