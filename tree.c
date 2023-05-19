#include "tree.h"



SingleSourceMovesTree *FindSingleSourceMoves(Board board, checkersPos *src)
{
    SingleSourceMovesTree movesTree;

    char source;
    source = findPositon(board, src);
    if (source != NULL)
    {
        movesTree.source = buildTreeHelper(Board board, checkersPos * src);
    }
    
}

char findPositon(Board board, checkersPos *src)
{
    char source;

    if ( (src->col < 1 || src->col > 8 ) || (src->row < 'A' || src->row > 'H'))
    {
        return NULL;
    }

    int row, col;

    row = src->row - '1';
    col = src->col - 'A';

    source = board[row][col];
    if (source = ' ')
        return NULL;
    else
        return source;
}

SingleSourceMovesTree buildTreeHelper(Board Board, checkersPos *src)
{
    if (source == NULL)
    {
        
    }
}

struct treeNode* createNewTNode(char source
{

}