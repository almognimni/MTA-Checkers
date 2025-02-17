
#ifndef PROJECT2_GENERAL_H
#define PROJECT2_GENERAL_H

#define _CRT_SECURE_NO_WARNINGS


/*Definitions*/
#include "board.h"
#include "tree.h"
#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


/*Functions*/

//Question 4
void turn(Board board, Player player);
SingleSourceMovesList * compareMoves(SingleSourceMovesList* lst1, SingleSourceMovesList* lst2, Player currentPlayer);
void executeMove(Board board, SingleSourceMovesList *executedMove, Player player);
void capture(Board board, checkersPos *current, checkersPos *next);
int max(int a, int b);

//Question 5
void PlayGame(Board board, Player starting_player);
void switchPlayer(Player* currentPlayer);
bool isOngoing (Board board);
bool isOutOfPieces(Board board);
void printStatistics(Player triumphantPlayer);

Player findCurrentPlayer(Board board, checkersPos *currentPosition);

//For main
Player chooseStartingPlayer();


#endif
