


#include "board.h"
#include "general.h"


int highestCaptures = 0;
char highestCapturesPlayer = '0';
int totalMovesT = 0;
int totalMovesB = 0;

int main()
{
    Board board;

    Player startingPlayer = chooseStartingPlayer();

    initializeBoard(board);

    makeEmptyBoard(board);

    board[2][2] = 'T';
    board[3][3] = 'B';
    board[3][0] = 'T';


    PlayGame(board, startingPlayer);
}

