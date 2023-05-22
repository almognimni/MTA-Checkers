#include "board.h"
#include <stdio.h>
#define BOARD_SIZE 8


void initializeBoard(Board board)
{
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < BOARD_SIZE; j++)
        {
            if ((i + j) % 2 == 0)
                board[i][j] = ' ';
            else if (i < 3)
                board[i][j] = 'T';
            else if (i > 4)
                board[i][j] = 'B';
            else
                board[i][j] = ' ';
        }
    }
}
/*
void initializeBoard(Board board)
{
    int i,j;
    for (i=0;i<BOARD_SIZE;i++)
    {
        for(j=0;j<BOARD_SIZE;j++)
        {
            if((i+j)%2==0)
                board[i][j]=' ';
            else if(i<3)
                board[i][j]='T';
            else if(i>4)
                board[i][j]='B';
        }
    }

}*/

void printBoard(Board board)
{
    int i = 0;
    int j = 0;

    printf("\n");

    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < BOARD_SIZE; j++)
        {
        printf("* %c  ", board[i][j]);
        }
        printf("\n");
    }
}