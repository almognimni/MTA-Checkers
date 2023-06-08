#include "general.h"


//Question 4
void turn(Board board, Player player)
{
    extern int highestCaptures;
    extern char highestCapturesPlayer;

    int longestMoves = 0, currentLenght;

    MultipleSourceMovesList *possibleMoves = FindAllPossiblePlayerMoves(board, player);

    SingleSourceMovesList *chosenList;
    SingleSourceMovesList *contender;

    MultipleSourceMovesListCell *current;
    current = possibleMoves->head;

    chosenList = current->single_source_moves_list;

    if(current->next == NULL)
    {
        executeMove(board, current, player);
        return;
    }

    while(current->next != NULL)
    {
        contender = current->next->single_source_moves_list;
        currentLenght = contender->tail->captures;

         if(currentLenght > longestMoves)
         {
             longestMoves = currentLenght;
             chosenList = contender;
         }

         else if(currentLenght == longestMoves)
         {
             chosenList = compareMoves(contender,chosenList, player);
         }
         current = current->next;

         if(currentLenght > highestCaptures)
         {
             highestCaptures = currentLenght;
             highestCapturesPlayer = player;
         }

    }

    executeMove(board, chosenList, player);
}

void executeMove(Board board, SingleSourceMovesList* executedMove, Player player)
{
    extern int totalMovesB, totalMovesT;
    checkersPos *startingPos, *endingPos, *currentPos, *nextPos;
    SingleSourceMovesListCell *current = executedMove->head;

    startingPos = executedMove->head->position;
    endingPos = executedMove->tail->position;

    printf("%c%c->%c%c", startingPos->row,startingPos->col,endingPos->row, endingPos->col);

    board[startingPos->row - 'A'][startingPos->col - '1'] = ' '; // delete the peice from its starting source

    while(current->next != NULL)
    {
        currentPos = current->position;

        nextPos = current->next->position;

        capture(board, currentPos, nextPos);

        current = current->next;

        if(player == 'B')
            totalMovesB++;
        else
            totalMovesT++;
    }
    board[endingPos->row -'A'][endingPos->col -'1'] = player;


}

void capture(Board board, checkersPos *current, checkersPos *next)
{
    int capturedRow, capturedCol, currentCol, currentRow, nextRow, nextCol;

    getIndex(current, &currentRow, &currentCol);
    getIndex(next, &nextRow, &nextCol);

    capturedRow = (currentRow + nextRow) / 2;
    capturedCol = (currentCol + nextCol) / 2;

    board[capturedRow][capturedCol] = ' ';

}



int max(int a, int b)
{
    return a > b ? a : b;
}

void PlayGame (Board board, Player starting_player)
{
    bool ongoing = true;

    while (true)
    {
        printf("\n%c's turn:\n", starting_player);

        turn(board, starting_player);

        printBoard(board);

        ongoing = isOngoing(board);

        if (!ongoing)
        {
            break;
        }

        switchPlayer(&starting_player);
    }

    printf("%c Wins!", starting_player);

    printStatistics(board, starting_player);

}

void switchPlayer(Player* currentPlayer)
{
    if (*currentPlayer == 'B')
    {
        *currentPlayer = 'T';
    }
    else
    {
        *currentPlayer = 'B';
    }
}

bool isOngoing (Board board)
{
    int col;

    for(col = 0; col < BOARD_SIZE; col++)
    {
        if(board[0][col] == 'B')
            return false;

        if(board[7][col] == 'T')
            return false;
    }

    return isOutOfPieces(board);
}

bool isOutOfPieces(Board board)
{
    bool isBExist = false, isTExist = false;

    int i,j;
    for ( i = 0; i < BOARD_SIZE; i++)
    {
        for ( j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == 'B')
            {
                isBExist = true;
            }

            if (board[i][j] == 'T')
            {
                isTExist = true;
            }

            if (isBExist && isTExist)
            {
                break;
            }
        }
    }
    return (isTExist && isBExist);
}

void printStatistics(Board board, Player triumphantPlayer)
{
    extern int totalMovesB, totalMovesT, highestCaptures;
    extern char highestCapturesPlayer;

    if(triumphantPlayer == 'B')
        printf("%C performed %d moves.", triumphantPlayer, totalMovesB);

    else if(triumphantPlayer == 'T')
        printf("%C performed %d moves.", triumphantPlayer, totalMovesT);

    printf("%C performed the highest number of captures in a single move - %d", highestCapturesPlayer, highestCaptures);
}

Player chooseStartingPlayer()
{
    bool validChoice = false;
    int choise;
    printf("Enter 1 for T or 0 for B");

    do {
        scanf("%d", &choise);

        switch (choise)
        {
            case 0:
                return 'B';

            case 1:
                return 'T';

            default:
                printf("Invalid choice, please enter 0 or 1");
                break;
        }
    } while (!validChoice);

}