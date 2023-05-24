#include "tree.h"
#include "board.h"

#define B 0
#define T 1


#define LEFT 0
#define RIGHT 1

SingleSourceMovesTree *FindSingleSourceMoves(Board board, checkersPos *src)
{
    int row = 0, col = 0;
    getIndex(src,&row,&col);

    unsigned short totalCapturesSoFar = 0;

    SingleSourceMovesTree *tree;
    tree = malloc(sizeof(SingleSourceMovesTree));

    int sourceSide = isBorT(board, row, col);

    tree->source = buildTreeHelper(board, row, col, sourceSide, &totalCapturesSoFar);
    return tree;
}




/*
SingleSourceMovesTreeNode* buildTreeHelper(Board board, int row, int col, int sourceSide, unsigned short* totalCaptures) //isNodeParamNeeded
{
//Add base case for null or opposite side
    SingleSourceMovesTreeNode *node;

    if (isInRange(row, col) == false)
    {
        return NULL;
    }

    if(board[row][col] == " ")
    {

    }
        node = createNewTNode(board, row, col, totalCaptures);

        switch (sourceSide)
        {
            case B:
                if ((isInRange(row, col)) && (board[row - 1][col - 1] == 'T') && (board[row - 2][col - 2] != ' ')) //LEFT
                {
                    node->next_moves[LEFT] = buildTreeHelper(board, row - 2, col - 2, sourceSide, totalCaptures + 1);
                }
                if ((isInRange(row, col)) && (board[row - 1][col + 1] == 'T') && (board[row - 2][col + 2] != ' ')) //RIGHT
                {
                    node->next_moves[RIGHT] = buildTreeHelper(board, row - 2, col + 2, sourceSide, totalCaptures + 1);
                }
                break;

            case T:
                if ((isInRange(row, col)) && (board[row + 1][col + 1] == 'B') && (board[row + 2][col + 1] != ' ')) //LEFT (By it's perspective)
                {
                    node->next_moves[LEFT] = buildTreeHelper(board, row + 2, col + 2, sourceSide, totalCaptures + 1);
                }
                if ((isInRange(row, col)) && (board[row + 1][col - 1] == 'B') && (board[row + 2][col - 2] != ' ')) //RIGHT (By it's perspective)
                {
                    node->next_moves[RIGHT] = buildTreeHelper(board, row + 2, col - 2, sourceSide, totalCaptures + 1);
                }
                break;

            default:
                printf("If printed - switch has uncovered case");
                return NULL;
        }
    return node;
}*/


//chat
SingleSourceMovesTreeNode* buildTreeHelper(Board board, int row, int col, int sourceSide, unsigned short* totalCaptures)
{
    SingleSourceMovesTreeNode *node;

    if (isInRange(row, col) == false)
    {
        return NULL;
    }


    node = createNewTNode(board, row, col, totalCaptures);

    switch (sourceSide)
    {
        case B:
            // Capture moves
            if (isInRange(row - 2, col - 2) && board[row - 1][col - 1] == 'T' && board[row - 2][col - 2] == ' ')
            {
                node->next_moves[LEFT] = buildTreeHelper(board, row - 2, col - 2, sourceSide, totalCaptures + 1);
            }
            if (isInRange(row - 2, col + 2) && board[row - 1][col + 1] == 'T' && board[row - 2][col + 2] == ' ')
            {
                node->next_moves[RIGHT] = buildTreeHelper(board, row - 2, col + 2, sourceSide, totalCaptures + 1);
            }
                // Regular moves
            else if (isInRange(row - 1, col - 1) && board[row - 1][col - 1] == ' ')
            {
                node->next_moves[LEFT] = buildTreeHelper(board, row - 1, col - 1, sourceSide, totalCaptures);
            }
            else if (isInRange(row - 1, col + 1) && board[row - 1][col + 1] == ' ')
            {
                node->next_moves[RIGHT] = buildTreeHelper(board, row - 1, col + 1, sourceSide, totalCaptures);
            }
            break;

        case T:
            // Capture moves
            if (isInRange(row + 2, col + 2) && board[row + 1][col + 1] == 'B' && board[row + 2][col + 2] == ' ')
            {
                node->next_moves[LEFT] = buildTreeHelper(board, row + 2, col + 2, sourceSide, totalCaptures + 1);
            }
            if (isInRange(row + 2, col - 2) && board[row + 1][col - 1] == 'B' && board[row + 2][col - 2] == ' ')
            {
                node->next_moves[RIGHT] = buildTreeHelper(board, row + 2, col - 2, sourceSide, totalCaptures + 1);
            }
                // Regular moves
            else if (isInRange(row + 1, col + 1) && board[row + 1][col + 1] == ' ')
            {
                node->next_moves[LEFT] = buildTreeHelper(board, row + 1, col + 1, sourceSide, totalCaptures);
            }
            else if (isInRange(row + 1, col - 1) && board[row + 1][col - 1] == ' ')
            {
                node->next_moves[RIGHT] = buildTreeHelper(board, row + 1, col - 1, sourceSide, totalCaptures);
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




//bool canMove(Board board, int row, int col, int sourceSide, int direction) //TIDY later
//{
//    switch(sourceSide)
//    {
//        case B:
//            switch(direction)
//            {
//                case LEFT:
//                    if ((isInRange(row, col)) && (board[row - 1][col - 1] == 'T'))
//                        return true;
//                    else
//                        return false;
//                    break;
//                case RIGHT:
//                    if ((isInRange(row, col)) && (board[row - 1][col + 1] == 'T') && (board[row - 2][col + 2] != ' '))
//            }
//    }
//}
//
// ((isInRange(row, col)) && (board[row - 1][col - 1] == 'T'))