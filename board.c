#include "board.h"

//This function takes a Board object as a parameter and initializes its values based on the rules of checkers
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

//This function takes a board type (chars array) and prints it
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
//Takes a pointer and terminates the program if it's null
void checkMemoryAllocationPos(checkersPos *pos)
{
    if (pos == NULL)
    {
        printf("Memory allocation error!!!\n");
        exit(1);
    }
}

//Takes a src struct (2 chars) and converts them to integers
void getIndex(checkersPos *src, int *row, int *col)
{
    *row = (src->row - 'A');
    *col = (src->col - '1');
}

//This function checks the value of a specific cell in a 2D board represented by the board array.
//If the value at the specified cell is 'B', the function returns the value 0.
//If the value at the specified cell is 'T', the function returns the value 1.
int isBorT(Board board, int row, int col)
{
    if (board[row][col] == 'B')
    {
        return B;
    }
    else if (board[row][col] == 'T')
    {
        return T;
    }
}

//The function checks if the given indices are valid for accessing elements in a 8x8 board.
bool isInRange(int row, int col)
{
    if (row < 0 || row >= 8 || col < 0 || col >= 8)
        return false;
    else
        return true;
}

//Debugging

void makeEmptyBoard(Board board)
{
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < BOARD_SIZE; j++)
        {

            board[i][j] = ' ';
        }
    }
}