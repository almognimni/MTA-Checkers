#ifndef PROJECT_TREE_H
#define PROJECT_TREE_H

/*Libraries*/

#include "board.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*Definitions*/
#define B 0
#define T 1

#define LEFT 0
#define RIGHT 1


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

SingleSourceMovesTree *FindSingleSourceMoves(Board board, checkersPos *src);
SingleSourceMovesTreeNode* createNewTNode(Board board, int row, int col, unsigned short *total_captures_so_far);
SingleSourceMovesTreeNode* buildTreeHelper(Board board, int row, int col, int sourceSide, unsigned short* totalCaptures,bool *captured);

void checkMemoryAllocationTree(SingleSourceMovesTreeNode *treeNode); //VOID

void printTreeHelper(SingleSourceMovesTreeNode *root);

int heightHelper(SingleSourceMovesTreeNode *root);
int height(SingleSourceMovesTree *tr);

void freeTree(SingleSourceMovesTree * tr);
void freeTreeHelper(SingleSourceMovesTreeNode *root);

#endif

