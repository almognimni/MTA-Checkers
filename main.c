//Almog Nimni
//ID: 319090593

//Betty Halmish
//ID: 209363555

#define _CRT_SECURE_NO_WARNINGS

#include "board.h"
#include "tree.h"
#include "list.h"
#include "general.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define STARTING_PLAYER 'B'

int highestCaptures = 0;
char highestCapturesPlayer = '0';
int totalMovesT = 0;
int totalMovesB = 0;

int main()
{
    Board board;

    Player startingPlayer = STARTING_PLAYER;

    initializeBoard(board);

    PlayGame(board, startingPlayer);

//    tree = FindSingleSourceMoves(board, src);

    //SingleSourceMovesList *testList = FindSingleSourceOptimalMove(tree); //Question 2
    //printTreeInorder(tree);

    //printList(testList);

//    MultipleSourceMovesList *multiList = FindAllPossiblePlayerMoves(board, 'T'); //Question 3
    //printMultiList(multiList);




}

