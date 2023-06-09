#include "tree.h"
#include "board.h"
#include "general.h"

#define B 0
#define T 1


#define LEFT 0
#define RIGHT 1

SingleSourceMovesTree *FindSingleSourceMoves(Board board, checkersPos *src)
{
    bool captured = false;

    int row = 0, col = 0;
    getIndex(src,&row,&col);

    unsigned short totalCapturesSoFar = 0;

    SingleSourceMovesTree *tree;
    tree = malloc(sizeof(SingleSourceMovesTree));

    int sourceSide = isBorT(board, row, col);

    tree->source = buildTreeHelper(board, row, col, sourceSide, &totalCapturesSoFar, &captured);
    return tree;

}


SingleSourceMovesTreeNode* buildTreeHelper(Board board, int row, int col, int sourceSide, unsigned short* totalCaptures,bool *captured)
{
    SingleSourceMovesTreeNode *node;

    if (isInRange(row, col) == false)
    {
        return NULL;
    }

    node = createNewTNode(board, row, col, totalCaptures);

        if (*captured == true)
        {
            switch (sourceSide)
            {
                case B:
                    if (board[row - 1][col - 1] != 'T' && board[row - 1][col + 1] != 'T')
                    {
                        return node;
                    }

                case T:
                    if (board[row + 1][col - 1] != 'B' && board[row + 1][col + 1] != 'B')
                    {
                        return node;
                    }
            }
        }

    switch (sourceSide)
    {
        case B:
            // Capture moves
            if (isInRange(row - 2, col - 2) && board[row - 1][col - 1] == 'T' && board[row - 2][col - 2] == ' ')
            {
                unsigned short totalCapturesLeft = *(totalCaptures) + 1;
                *captured = true;
                node->next_moves[LEFT] = buildTreeHelper(board, row - 2, col - 2, sourceSide, &totalCapturesLeft, captured);
            }
            if (isInRange(row - 2, col + 2) && board[row - 1][col + 1] == 'T' && board[row - 2][col + 2] == ' ')
            {
                unsigned short totalCapturesRight = *(totalCaptures) + 1;
                *captured = true;
                node->next_moves[RIGHT] = buildTreeHelper(board, row - 2, col + 2, sourceSide, &totalCapturesRight, captured);
            }
            else
            {
                // Regular moves
                if (isInRange(row - 1, col - 1) && board[row - 1][col - 1] == ' ')
                {
                    //node->next_moves[LEFT] = buildTreeHelper(board, row - 1, col - 1, sourceSide, totalCaptures);
                    node->next_moves[LEFT] = createNewTNode(board, row - 1, col - 1, totalCaptures);
                }
                if (isInRange(row - 1, col + 1) && board[row - 1][col + 1] == ' ')
                {
                    //node->next_moves[RIGHT] = buildTreeHelper(board, row - 1, col + 1, sourceSide, totalCaptures);
                    node->next_moves[RIGHT] = createNewTNode(board, row - 1, col + 1, totalCaptures);
                }
            }
            break;

        case T:
            // Capture moves
            if (isInRange(row + 2, col + 2) && board[row + 1][col + 1] == 'B' && board[row + 2][col + 2] == ' ')
            {
                unsigned short totalCapturesLeft = *(totalCaptures) + 1;
                *captured = true;
                node->next_moves[LEFT] = buildTreeHelper(board, row + 2, col + 2, sourceSide, &totalCapturesLeft, captured);
            }
            if (isInRange(row + 2, col - 2) && board[row + 1][col - 1] == 'B' && board[row + 2][col - 2] == ' ')
            {
                unsigned short totalCapturesRight = *(totalCaptures) + 1;
                *captured = true;
                node->next_moves[RIGHT] = buildTreeHelper(board, row + 2, col - 2, sourceSide, &totalCapturesRight, captured);

            }
                // Regular moves
            else
            {
                if (isInRange(row + 1, col + 1) && board[row + 1][col + 1] == ' ')
                {
                    //node->next_moves[LEFT] = buildTreeHelper(board, row + 1, col + 1, sourceSide, totalCaptures);
                    node->next_moves[LEFT] = createNewTNode(board, row + 1, col + 1, totalCaptures);
                }
                if (isInRange(row + 1, col - 1) && board[row + 1][col - 1] == ' ')
                {
                    //node->next_moves[RIGHT] = buildTreeHelper(board, row + 1, col - 1, sourceSide, totalCaptures);
                    node->next_moves[RIGHT] = createNewTNode(board, row + 1, col - 1, totalCaptures);
                }
            }
            break;

        default:
            printf("If printed - switch has uncovered case");
            return NULL;
    }


    return node;
}



SingleSourceMovesTreeNode* createNewTNode(Board board, int row, int col, unsigned short *total_captures_so_far)
{
    SingleSourceMovesTreeNode *res;
    res = (SingleSourceMovesTreeNode*) malloc(sizeof (SingleSourceMovesTreeNode));
    checkMemoryAllocationTree(res);

    memcpy(res->board, board, sizeof(board)); //???
    res->total_captures_so_far = *(total_captures_so_far);

    res->pos = (checkersPos*) malloc (sizeof (checkersPos));
    res->pos->row = (char)(row + 'A'); // create function
    res->pos->col = (char)(col + '1'); //likewise

    res->next_moves[LEFT] = NULL;
    res->next_moves[RIGHT] = NULL;

    return res;
}

void checkMemoryAllocationTree(SingleSourceMovesTreeNode *treeNode)
{
    if (treeNode == NULL)
    {
        printf("Memory allocation error!!!\n");
        exit(1);
    }
}

void printTreeInorder(SingleSourceMovesTree *tr)
{
    printTreeHelper(tr->source);
    printf("\n");
}

void printTreeHelper(SingleSourceMovesTreeNode *root)
{
    if (root == NULL)
        return;
    else
    {
        printTreeHelper(root->next_moves[LEFT]);
        printf(" %c%c ", root->pos->row, root->pos->col); //add captures
        printTreeHelper(root->next_moves[RIGHT]);
    }
}

int height(SingleSourceMovesTree *tr)
{
    return heightHelper(tr->source);
}

int heightHelper(SingleSourceMovesTreeNode *root)
{
    int heightLeft, heightRight;
    if(root == NULL)
        return -1;
    else
    {
        //if (root->next_moves[LEFT] != NULL)
            heightLeft = heightHelper(root->next_moves[LEFT]);

        //if (root->next_moves[RIGHT] != NULL)
            heightRight = heightHelper(root->next_moves[RIGHT]);

        return 1 + max(heightLeft, heightRight);
    }
}

// free all memory of a tree
void freeTree(SingleSourceMovesTree * tr)
{
    freeTreeHelper(tr->source);
    tr->source = NULL;
}

void freeTreeHelper(SingleSourceMovesTreeNode *root)
{
    if (root == NULL)
        return;
    else
    {
        freeTreeHelper(root->next_moves[LEFT]);
        freeTreeHelper(root->next_moves[RIGHT]);
        free (root);
    }
}
