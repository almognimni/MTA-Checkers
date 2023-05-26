//Almog Nimni
//ID: 319090593

//Betty Halmish
//Id: 209363555

#define _CRT_SECURE_NO_WARNINGS

#include "board.h"
#include "tree.h"
#include "lists.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main()
{
    Board board;
    checkersPos *src;

    SingleSourceMovesTree *tree;

    src = (checkersPos*)malloc(sizeof (checkersPos));

    src->row = 'C';
    src->col = '2';

    initializeBoard(board);
    //printBoard(board);

    tree = FindSingleSourceMoves(board, src);

    SingleSourceMovesList *testList = FindSingleSourceOptimalMove(tree);

    printList(testList);

    printTreeInorder(tree);


}

