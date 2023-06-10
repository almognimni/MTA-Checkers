#include "general.h"

//Question 4
void turn(Board board, Player player)
{
    extern int highestCaptures;
    extern char highestCapturesPlayer;

    int currentLength, contenderLength; // CHANGED NAMES

    MultipleSourceMovesList *possibleMoves = FindAllPossiblePlayerMoves(board, player);

    SingleSourceMovesList *chosenList;

    SingleSourceMovesList *contender;

    MultipleSourceMovesListCell *current;
    current = possibleMoves->head;

    chosenList = current->single_source_moves_list;
    currentLength = chosenList->tail->captures; // NEW


    if(current->next == NULL)
    {
        executeMove(board, chosenList, player); //changed current to chosen list
        return;
    }

    while(current->next != NULL)
    {
        contender = current->next->single_source_moves_list;
        contenderLength = contender->tail->captures;

         if(contenderLength > currentLength)
         {
             currentLength = contenderLength;
             chosenList = contender;
         }

         else if(contenderLength == currentLength)
         {
             chosenList = compareMoves(contender,chosenList, player);
         }
         current = current->next;

         if(contenderLength > highestCaptures)
         {
             highestCaptures = contenderLength;
             highestCapturesPlayer = player;
         }
    }



    executeMove(board, chosenList, player);
}

void executeMove(Board board, SingleSourceMovesList* executedMove, Player player)
{
    checkersPos *startingPos, *endingPos, *currentPos, *nextPos;
    SingleSourceMovesListCell *current = executedMove->head;

    startingPos = executedMove->head->position;
    endingPos = executedMove->tail->position;

    printf("%c%c->%c%c", startingPos->row,startingPos->col,endingPos->row, endingPos->col);

    board[startingPos->row - 'A'][startingPos->col - '1'] = ' '; // delete the piece from its starting source

    while(current->next != NULL)
    {
        currentPos = current->position;

        nextPos = current->next->position;

        capture(board, currentPos, nextPos);

        current = current->next;

    }


    board[endingPos->row -'A'][endingPos->col -'1'] = player;
}

void capture(Board board, checkersPos *current, checkersPos *next)
{
    int capturedRow, capturedCol, currentCol, currentRow, nextRow, nextCol;

    getIndex(current, &currentRow, &currentCol);
    getIndex(next, &nextRow, &nextCol);

    extern int totalMovesB, totalMovesT;


    capturedRow = (currentRow + nextRow) / 2;
    capturedCol = (currentCol + nextCol) / 2;

    board[capturedRow][capturedCol] = ' ';

}

SingleSourceMovesList *compareMoves(SingleSourceMovesList* lst1, SingleSourceMovesList* lst2, Player currentPlayer)
{
    switch (currentPlayer)
    {
        case 'B':
            if ((lst1->head->position->row) < (lst2->head->position->row)) // Prefer lower letters
                return lst1;

            else if ((lst1->head->position->row) > (lst2->head->position->row))
                return lst2;

            else // at the same row
            {
                if ((lst1->head->position->col) < (lst2->head->position->col)) // Prefer lower numbers
                {
                    return lst1;
                }
                return lst2;
            }

        case 'T':
            if ((lst1->head->position->row) > (lst2->head->position->row)) // Prefer higher letters
                return lst1;

            else if ((lst1->head->position->row) < (lst2->head->position->row))
                return lst2;

            else
            {
                if ((lst1->head->position->col) > (lst2->head->position->col)) // Prefer higher numbers
                {
                    return lst1;
                }
                return lst2;

                default:
                    printf("♫ ♪ How did you get here? ↕ § $ ↑ ◙ ♂ ▬ ◙ ▲ ◙ ♀  Were you lost? ♫ ♥ ♪");
                exit(1);
            }
    }
}

int max(int a, int b)
{
    return a > b ? a : b;
}

void PlayGame (Board board, Player starting_player)
{
    bool ongoing = true;

    printBoard(board);

    while (true)
    {
        printf("%c's turn:\n", starting_player);

        turn(board, starting_player);

        printBoard(board);

        ongoing = isOngoing(board);

//        extern int totalMovesB,totalMovesT;
//
//        if(starting_player == 'B')
//            totalMovesB++;
//
//        else if(starting_player == 'T')
//            totalMovesT++;

        if (!ongoing)
        {
            //printBoard(board);
            break;
        }

        //NEW - counters here
        extern int totalMovesB,totalMovesT;

        if(starting_player == 'B')
            totalMovesB++;

        else if(starting_player == 'T')
            totalMovesT++;

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
        printf("%C performed %d moves.\n", triumphantPlayer, totalMovesT);

    printf("%C performed the highest number of captures in a single move - %d", highestCapturesPlayer, highestCaptures);
}

Player chooseStartingPlayer()
{
    bool validChoice = false;
    int choice;
    printf("Enter 1 for T or 0 for B");

    do {
        scanf("%d", &choice);

        switch (choice)
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

Player findCurrentPlayer(Board board, checkersPos *currentPosition) //NEW
{
    Player res;
    int row, col;
    getIndex(currentPosition, &row, &col);
    return board[row][col];
}