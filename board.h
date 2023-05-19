#ifndef PROJECT_BOARD_H
#define PROJECT_BOARD_H

#define BOARD_SIZE 8

typedef struct _checkersPos
{
    char row,col;
}checkersPos;

typedef unsigned char Board [BOARD_SIZE][BOARD_SIZE];
typedef unsigned char Player;

void initializeBoard()
{
    Board board;
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
}



#endif
//betty