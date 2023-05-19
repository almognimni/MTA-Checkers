#include "tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

SingleSourceMovesTree *FindSingleSourceMoves(Board board, checkersPos *src)
{
    SingleSourceMovesTree *tree;
    tree = malloc(sizeof(SingleSourceMovesTree));

    if(board[src->row][src->col] == ' ')
        return NULL;

    else
    {
        tree->source = buildTreeHelper(board, src);
        return tree;
    }
}

void buildTreeHelper(Board *board, SingleSourceMovesTreeNode *node, int row, int col, int is_capturing)
{
    if (row < 0 || row >= 8 || col < 0 || col >= 8)
        return;

    if (hasValidCapture(board, row, col, is_capturing))
    {
        node->next_moves[0] = createNewTNode(board, row + 1, col + 1);
        node->next_moves[1] = createNewTNode(board, row + 1, col - 1);
    }
    else
    {
        node->next_moves[0] = createNewTNode(board, row - 1, col + 1);
        node->next_moves[1] = createNewTNode(board, row - 1, col - 1);
    }
}



SingleSourceMovesTreeNode* createNewTNode(Board *board, int row, int col)
{
    SingleSourceMovesTreeNode *node = malloc(sizeof(SingleSourceMovesTreeNode));
    node->board = board;

    // Initialize the next move pointers to NULL
    node->next_moves[LEFT] = NULL;
    node->next_moves[RIGHT] = NULL;

    // Perform the recursive move generation
    buildTreeHelper(board, node, row, col, 0);

    return node;
}


