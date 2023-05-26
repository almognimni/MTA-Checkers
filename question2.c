//#include <stdio.h>
//#include <stdlib.h>
//#include <stdbool.h>
//
//#define BOARD_SIZE 8
//#define LEFT 0
//#define RIGHT 1
//
//typedef unsigned char Board [BOARD_SIZE][BOARD_SIZE];
//typedef unsigned char Player;
//
//typedef struct _checkersPos
//{
//    char row,col;
//}checkersPos;
//
//typedef struct _SingleSourceMovesTreeNode
//{
//    Board board;
//    checkersPos *pos;
//    unsigned short total_captures_so_far;
//    struct _SingleSourceMovesTreeNode *next_moves[2];
//
//}SingleSourceMovesTreeNode;
//
//typedef struct _SingleSourceMovesTree
//{
//    SingleSourceMovesTreeNode *source;
//}SingleSourceMovesTree;
//
//
//////////////////////////
//typedef struct _SingleSourceMovesListCell
//{
//    checkersPos *position;
//    unsigned short captures;
//    struct _SingleSourceMovesListCell *next;
//
//}SingleSourceMovesListCell;
//
//typedef struct _SingleSourceMovesList
//{
//    SingleSourceMovesListCell *head;
//    SingleSourceMovesListCell *tail;
//}SingleSourceMovesList;

////////////////////////////







int height(SingleSourceMovesTree *tr)
{
    return heightHelper(tr->source);
}

int heightHelper(SingleSourceMovesTreeNode *root)
{
    int heightLeft, heightRight;
    if(root == NULL)
        return -1;
    else
    {
        heightLeft = heightHelper(root->next_moves[LEFT]);
        heightRight = heightHelper(root->next_moves[RIGHT]);
        return 1 + max(heightLeft, heightRight);
    }
}

int max(int a, int b)
{
    return a > b ? a : b;
}




