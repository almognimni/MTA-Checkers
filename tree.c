#include "tree.h"
#include "board.h"
#include "general.h"

//The FindSingleSourceMoves function takes a board and a source position as input and returns a tree representing the possible moves from the source position on the board.
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

//Question 1
//the buildTreeHelper function is a helper function used by FindSingleSourceMoves to recursively build a tree of possible moves from a given source position on the board.
//If no capture has been made, the function checks for regular moves. It checks if there are empty spaces in the diagonal directions based on sourceSide and creates new nodes accordingly.
SingleSourceMovesTreeNode* buildTreeHelper(Board board, int row, int col, int sourceSide, unsigned short* totalCaptures,bool *captured)
{
    SingleSourceMovesTreeNode *node;

    //checks if the current position is within the valid range on the board
    if (isInRange(row, col) == false)
    {
        return NULL;
    }

    node = createNewTNode(board, row, col, totalCaptures);


        //checks if there are any additional capture moves possible from the current position
        if (*captured == true)
        {
            switch (sourceSide)
            {
                case B:
                    if (board[row - 1][col - 1] != 'T' && board[row - 1][col + 1] != 'T')
                    {
                        return node;
                    }
                    break;
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
                    //creates a new node for the current position.
                    node->next_moves[LEFT] = createNewTNode(board, row - 1, col - 1, totalCaptures);
                }
                if (isInRange(row - 1, col + 1) && board[row - 1][col + 1] == ' ')
                {
                    // creates a new node for the current position.
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
                    node->next_moves[LEFT] = createNewTNode(board, row + 1, col + 1, totalCaptures);
                }
                if (isInRange(row + 1, col - 1) && board[row + 1][col - 1] == ' ')
                {
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

// the function returns the newly created node res,
// which represents a position on the board with its associated information, such as the board state, total captures, and position indices.
SingleSourceMovesTreeNode* createNewTNode(Board board, int row, int col, unsigned short *total_captures_so_far)
{
    SingleSourceMovesTreeNode *res;
    res = (SingleSourceMovesTreeNode*) malloc(sizeof (SingleSourceMovesTreeNode));
    checkMemoryAllocationTree(res);

    memcpy(res->board, board, sizeof(unsigned char) * BOARD_SIZE * BOARD_SIZE);
    res->total_captures_so_far = *(total_captures_so_far);

    res->pos = (checkersPos*) malloc (sizeof (checkersPos));
    checkMemoryAllocationPos(res->pos);

    res->pos->row = (char)(row + 'A');
    res->pos->col = (char)(col + '1');

    res->next_moves[LEFT] = NULL;
    res->next_moves[RIGHT] = NULL;

    return res;
}

//If the treeNode is indeed NULL, the function prints an error message indicating a memory allocation error.
void checkMemoryAllocationTree(SingleSourceMovesTreeNode *treeNode)
{
    if (treeNode == NULL)
    {
        printf("Memory allocation error!!!\n");
        exit(1);
    }
}

//The height function takes a SingleSourceMovesTree pointer tr as input and calls the heightHelper function with the root node of the tree (tr->source).
// It then returns the result obtained from heightHelper, which represents the height of the tree.
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
            heightLeft = heightHelper(root->next_moves[LEFT]);
            heightRight = heightHelper(root->next_moves[RIGHT]);

        return 1 + max(heightLeft, heightRight);
    }
}

//Free all memory of a tree
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


//For debugging

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