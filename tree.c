#include "tree.h"
#include "board.h"

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
    unsigned short totalCapturesSoFar = 0;

    SingleSourceMovesTree *tree;
    tree = malloc(sizeof(SingleSourceMovesTree));

    int sourceSide = isBorT(board, src->row, src->col);

    tree->source = buildTreeHelper(board, src->row, src->col, sourceSide, &totalCapturesSoFar);
    return tree;
}


SingleSourceMovesTreeNode* test(Board board, int row, int col, int sourceSide, unsigned short* totalCaptures) //isNodeParamNeeded
{
//Add base case for null or opposite side
    SingleSourceMovesTreeNode *node;

    if (isInRange(row, col) == false)
    {
        return NULL;
    }

        node = createNewTNode(board, row, col, totalCaptures);

        switch (sourceSide)
        {
            case B:
                if ((isInRange(row, col)) && (board[row - 1][col - 1] == 'T') && (board[row - 2][col - 2] != ' ')) //LEFT
                {
                    node->next_moves[LEFT] = buildTreeHelper(board, row - 2, col - 2, sourceSide, totalCaptures + 1);
                }
                if ((isInRange(row, col)) && (board[row - 1][col + 1] == 'T') && (board[row - 2][col + 2] != ' ')) //RIGHT
                {
                    node->next_moves[RIGHT] = buildTreeHelper(board, row - 2, col + 2, sourceSide, totalCaptures + 1);
                }
                break;

            case T:
                if ((isInRange(row, col)) && (board[row + 1][col + 1] == 'B') && (board[row + 2][col + 1] != ' ')) //LEFT (By it's perspective)
                {
                    node->next_moves[LEFT] = buildTreeHelper(board, row + 2, col + 2, sourceSide, totalCaptures + 1);
                }
                if ((isInRange(row, col)) && (board[row + 1][col - 1] == 'B') && (board[row + 2][col - 2] != ' ')) //RIGHT (By it's perspective)
                {
                    node->next_moves[RIGHT] = buildTreeHelper(board, row + 2, col - 2, sourceSide, totalCaptures + 1);
                }
                break;

            default:
                printf("If printed - switch has uncovered case");
        }
    return node;
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

SingleSourceMovesTreeNode* createNewTNode(Board board, int row, int col, unsigned short *total_captures_so_far)
{
    SingleSourceMovesTreeNode *res;
    memcpy(res->board, board, BOARD_SIZE); //???
    res->total_captures_so_far = *(total_captures_so_far);
    res->pos->row = row;
    res->pos->col = col;
}


void printTreeInorder(SingleSourceMovesTree tr)
{
    printTreeHelper(tr.source);
    printf("\n");
}

void printTreeHelper(SingleSourceMovesTreeNode *root)
{
    if (root == NULL)
        return;
    else
    {
        printTreeHelper(root->next_moves[0]);
        printf("%d ", root->data);
        printTreeHelper(root->next_moves[1]);
    }
}


bool isInRange(int row, int col)
{
    if (row < 0 || row >= 8 || col < 0 || col >= 8)
        return false;
    else
        return true;
}

//bool canMove(Board board, int row, int col, int sourceSide, int direction) //TIDY later
//{
//    switch(sourceSide)
//    {
//        case B:
//            switch(direction)
//            {
//                case LEFT:
//                    if ((isInRange(row, col)) && (board[row - 1][col - 1] == 'T'))
//                        return true;
//                    else
//                        return false;
//                    break;
//                case RIGHT:
//                    if ((isInRange(row, col)) && (board[row - 1][col + 1] == 'T') && (board[row - 2][col + 2] != ' '))
//            }
//    }
//}
//
// ((isInRange(row, col)) && (board[row - 1][col - 1] == 'T'))