#include "board.h"


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


void printBoard(Board board)
{
    int i, j;
    char line = 'A';

    printf("\n+-+-+-+-+-+-+-+-+-+\n+ |1|2|3|4|5|6|7|8|\n");

    for (i = 0; i < BOARD_SIZE; i++)
    {
        printf("+-+-+-+-+-+-+-+-+-+\n");

        printf("|%c", line);
        line++;

        for (j = 0; j < BOARD_SIZE; j++)
        {
            printf("|%c", board[i][j]);
        }

        printf("|\n");

    }
    printf("+-+-+-+-+-+-+-+-+-+\n\n");

    fflush(stdout);
}

void checkMemoryAllocationPos(checkersPos *pos)
{
    if (pos == NULL)
    {
        printf("Memory allocation error!!!\n");
        exit(1);
    }
}


void getIndex(checkersPos *src, int *row, int *col)
{
    *row = (src->row - 'A');
    *col = (src->col - '1');
}

int isBorT(Board board, int row, int col)
{
    if (board[row][col] == 'B') //is string or char
    {
        return B;
    }
    else if (board[row][col] == 'T')
    {
        return T;
    }
}

bool isInRange(int row, int col)
{
    if (row < 0 || row >= 8 || col < 0 || col >= 8)
        return false;
    else
        return true;
}
