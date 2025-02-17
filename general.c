#include "general.h"

//Question 4
//the turn function represents a player's turn in the game.
// It finds all possible moves for the player, evaluates each move based on the number of captures made and their positions,
// selects the move with the longest length or compares moves if there are ties,
// updates the highest number of captures, and executes the chosen move on the game board.
void turn(Board board, Player player)
{
    extern int highestCaptures;
    extern char highestCapturesPlayer;

    int currentLength, contenderLength;

    MultipleSourceMovesList *possibleMoves = FindAllPossiblePlayerMoves(board, player);

    SingleSourceMovesList *chosenList;

    SingleSourceMovesList *contender;

    MultipleSourceMovesListCell *current;
    current = possibleMoves->head;

    chosenList = current->single_source_moves_list;
    currentLength = chosenList->tail->captures;


    if(current->next == NULL)
    {
        executeMove(board, chosenList, player);
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

// the executeMove function executes a move on the game board based on the provided SingleSourceMovesList. It updates the board by moving the piece, performing captures along the way, and sets the final position of the move. The capture function is a helper function used by executeMove to capture a piece on the game board.
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

//The capture function captures a checker piece by removing it from the board, given the current position and the next position of the moving checker piece.
void capture(Board board, checkersPos *current, checkersPos *next)
{
    int capturedRow, capturedCol, currentCol, currentRow, nextRow, nextCol;

    getIndex(current, &currentRow, &currentCol);
    getIndex(next, &nextRow, &nextCol);

    capturedRow = (currentRow + nextRow) / 2;
    capturedCol = (currentCol + nextCol) / 2;

    board[capturedRow][capturedCol] = ' ';
}


// The function compares two SingleSourceMovesList pointers based on the current player's turn.
// It returns the pointer that represents a move closer to the opponent's side, considering the row and column values of the head positions.
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


//The function determines and returns the larger of the two input values, a and b.
int max(int a, int b)
{
    return a > b ? a : b;
}

// the PlayGame function sets up a gameplay loop where players take turns,
// updates the game board and player turns, checks for game completion,
// and displays the winning player and additional statistics after the game ends.
void PlayGame (Board board, Player starting_player)
{
    bool ongoing = true;
    extern int totalMovesB,totalMovesT;

    printBoard(board);

    while (true)
    {
        printf("%c's turn:\n", starting_player);

        turn(board, starting_player);

        printBoard(board);

        ongoing = isOngoing(board);

        if (!ongoing)
        {
            break;
        }

        //For statistics
        if(starting_player == 'B')
            totalMovesB++;

        else if(starting_player == 'T')
            totalMovesT++;

        switchPlayer(&starting_player);
    }

    printf("%c Wins!", starting_player);

    printStatistics(starting_player);

}


//the function swaps the current player between 'B' and 'T'.
// After calling this function, the value of the currentPlayer pointer will be updated to reflect the new player for the next turn in the game
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


//The function checks if either player 'B' or 'T' has a piece in the top or bottom row of the game board.
// If so, it returns false, indicating that the game is not ongoing. Otherwise, it calls the isOutOfPieces function to determine if both players are still present on the board and returns the result.
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

//The function determines if both players 'B' and 'T' exist on the game board by iterating through each cell and setting boolean variables accordingly.
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

//The function prints statistics related to the total moves performed by the triumphant player and the player with the highest number of captures in a single move.
void printStatistics(Player triumphantPlayer)
{
    extern int totalMovesB, totalMovesT, highestCaptures;
    extern char highestCapturesPlayer;

    if(triumphantPlayer == 'B')
        printf("%C performed %d moves.", triumphantPlayer, totalMovesB);

    else if(triumphantPlayer == 'T')
        printf("%C performed %d moves.\n", triumphantPlayer, totalMovesT);

    printf("%C performed the highest number of captures in a single move - %d", highestCapturesPlayer, highestCaptures);
}

// The function prompts the player for a choice of 'B' or 'T',
// validates the input, and returns the chosen character.
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

// Takes a board and a position, Returns the player on that position.
Player findCurrentPlayer(Board board, checkersPos *currentPosition)
{
    int row, col;
    getIndex(currentPosition, &row, &col);
    return board[row][col];
}