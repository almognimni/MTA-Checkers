#include "tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define B 0
#define T 1
#define LEFT 0
#define RIGHT 1

SingleSourceMovesTree *FindSingleSourceMoves(Board board, checkersPos *src)
{
    int totalCapturesSoFar = 0;

    SingleSourceMovesTree *tree;
    tree = malloc(sizeof(SingleSourceMovesTree));

    int sourceSide = isBorT(board, src->row, src->col);

    if(board[src->row][src->col] == ' ')
        return NULL;

    else
    {
        tree->source = buildTreeHelper(board, src->row, src->col, sourceSide, &totalCapturesSoFar);
        return tree;
    }
}

SingleSourceMovesTreeNode* buildTreeHelper(Board *board, int row, int col, int sourceSide, int* totalCaptures) //isNodeParamNeeded
{
//Add base case for null or opossite side
    SingleSourceMovesTreeNode *node;

    if (row < 0 || row >= 8 || col < 0 || col >= 8)
    {
        return NULL;
    }
    else if (board[row][col] == ' ')
    {
        node = createNewTNode(board, row, col, totalCaptures);
        return node;
    }


    if (isBorT(board, row, col) == B)
    {
        if (board[row - 1][col - 1] == 'T') //LEFT
        {
        node->next_moves[LEFT] = buildTreeHelper(board, row - 2, col - 2, sourceSide, totalCaptures + 1);
        }
        if (board[row - 1][col + 1] == 'T') //RIGHT
        {
        node->next_moves[RIGHT] = buildTreeHelper(board, row - 2, col + 2, sourceSide, totalCaptures + 1);
        }
    }
    else //Source is T
    {
        if (board[row + 1][col + 1] == 'T') //LEFT
        {
        node->next_moves[LEFT] = buildTreeHelper(board, row + 2, col + 2, sourceSide, totalCaptures + 1);
        }
        if (board[row + 1][col - 1] == 'T') //RIGHT
        {
        node->next_moves[RIGHT] = buildTreeHelper(board, row + 2, col - 2, sourceSide, totalCaptures + 1);
        }
    }
    
}


int isBorT(Board board, int row, int col)
{
    if (board[row][col] == 'B') //is string or char
    {
        return B;
    }
    else if (board[row][col] == 'T')
    {
        return T;
    }
}

SingleSourceMovesTreeNode* createNewTNode(Board board, int row, int col, unsigned short total_captures_so_far)
{
    SingleSourceMovesTreeNode *res;
    res->board = board; //???
    res->total_captures_so_far = total_captures_so_far;
    res->pos->row = row;
    res->pos->col = col;
}
