#ifndef PROJECT_BOARD_H
#define PROJECT_BOARD_H

#define BOARD_SIZE 8

typedef struct _checkersPos
{
    char row,col;
}checkersPos;


typedef unsigned char Board [BOARD_SIZE][BOARD_SIZE];
typedef unsigned char Player;
void initializeBoard();

#endif
//betty