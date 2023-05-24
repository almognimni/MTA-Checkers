#ifndef PROJECT_BOARD_H
#define PROJECT_BOARD_H

#include <stdio.h>
#include <stdbool.h>

#define BOARD_SIZE 8

#define B 0
#define T 1

#define LEFT 0
#define RIGHT 1


typedef struct _checkersPos
{
    char row,col;
}checkersPos;


typedef unsigned char Board [BOARD_SIZE][BOARD_SIZE];
typedef unsigned char Player;
void initializeBoard();
void printBoard(Board board);
void getIndex(checkersPos *src, int *row, int *col);
int isBorT(Board board, int row, int col);
bool isInRange(int row, int col);

#endif
//betty