#ifndef PROJECT_TREE_H
#define PROJECT_TREE_H

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
SingleSourceMovesTree buildTreeHelper(Board Board, checkersPos *src);
char findPositon(Board board, checkersPos *src);

#endif
