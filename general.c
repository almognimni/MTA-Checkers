#include "general.h"

//Question 4
void turn(Board board, Player player)
{
    int longestMoves = 0, currentLenght;

    MultipleSourceMovesList *possibleMoves = FindAllPossiblePlayerMoves(board, player);

    SingleSourceMovesList *chosenList;
    SingleSourceMovesList *contender;

    MultipleSourceMovesListCell *current;
    current = possibleMoves->head;

    while(current != NULL)
    {
        contender = current->single_source_moves_list;
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
    }
    executeMove(board, chosenList, player);
}

void executeMove(Board board, SingleSourceMovesList* executedMove, Player player)
{
    checkersPos *startingPos, *endingPos, *currentPos, *nextPos;

    SingleSourceMovesListCell *current = executedMove->head;

    startingPos = executedMove->head->position;
    endingPos = executedMove->tail->position;

    board[startingPos->row][startingPos->col] = ' ';

    while(current->next != NULL)
    {
        currentPos = current->position;

        nextPos = current->next->position;

        capture(board, currentPos, nextPos);

        current = current->next;
    }
    board[endingPos->row][endingPos->col] = player;
}


void capture(Board board, checkersPos *current, checkersPos *next)
{
    char capturedRow, capturedCol, currentCol, currentRow, nextRow, nextCol;

    getIndex(current, &currentRow, &currentCol);
    getIndex(next, &nextRow, &nextCol);

    capturedRow = (currentRow + nextRow) / 2;
    capturedCol = (currentCol + nextCol) / 2;

    board[currentRow][currentCol] = ' ';
}



int max(int a, int b)
{
    return a > b ? a : b;
}
