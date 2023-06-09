
#ifndef PROJECT2_GENERAL_H
#define PROJECT2_GENERAL_H

#include "board.h"
#include "tree.h"
#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

SingleSourceMovesList * compareMoves(SingleSourceMovesList* lst1, SingleSourceMovesList* lst2, Player currentPlayer);
void executeMove(Board board, SingleSourceMovesList *executedMove, Player player);
int findListLength(SingleSourceMovesList* singleList);
void capture(Board board, checkersPos *current, checkersPos *next);
void turn(Board board, Player player);
int max(int a, int b);
void PlayGame(Board board, Player starting_player);
void switchPlayer(Player* currentPlayer);
bool isOngoing (Board board);
bool isOutOfPieces(Board board);
void printStatistics(Board board, Player triumphantPlayer);
#endif
