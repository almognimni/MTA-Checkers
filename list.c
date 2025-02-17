#include "list.h"
#include "general.h"

//Question 2
//Input: A pointer to a SingleSourceMovesTree data structure.
//Function: This function computes the optimal move in the given moves tree. It traverses the tree, keeping track of the optimal move using a helper function.
//Return: Returns a pointer to a SingleSourceMovesList data structure that contains the optimal move(s).
SingleSourceMovesList *FindSingleSourceOptimalMove(SingleSourceMovesTree *moves_tree)
{
    Player currentPlayer = findCurrentPlayer(moves_tree->source->board, moves_tree->source->pos);

    SingleSourceMovesList *optimalMoveList;

    optimalMoveList = (SingleSourceMovesList*) malloc(sizeof (SingleSourceMovesList));
    checkMemoryAllocationList(optimalMoveList);

    makeEmptyList(optimalMoveList);

    FindOptimalMoveHelper(moves_tree->source,optimalMoveList,currentPlayer);

    return optimalMoveList;

}

/*Input: A pointer to a SingleSourceMovesTreeNode data structure and a pointer to a SingleSourceMovesList.
Function: This helper function is used by the FindSingleSourceOptimalMove function to traverse the tree and insert each node into the list.*/
void FindOptimalMoveHelper(SingleSourceMovesTreeNode *treeNode ,SingleSourceMovesList *list ,Player currentPlayer)
{
    int heightRight, heightLeft;

    if (treeNode == NULL)
    {
        return;
    }

    insertDataToEndList(list, treeNode);

    if (treeNode->next_moves[LEFT] == NULL && treeNode->next_moves[RIGHT] == NULL)
        return;

    else if (treeNode->next_moves[LEFT] == NULL)
        return FindOptimalMoveHelper(treeNode->next_moves[RIGHT], list, currentPlayer);

    else if (treeNode->next_moves[RIGHT] == NULL)
        return FindOptimalMoveHelper(treeNode->next_moves[LEFT], list, currentPlayer);


    heightLeft = heightHelper(treeNode->next_moves[LEFT]);
    heightRight = heightHelper(treeNode->next_moves[RIGHT]);

    if (heightRight > heightLeft)
    {
        return FindOptimalMoveHelper(treeNode->next_moves[RIGHT], list, currentPlayer);
    }

    if (heightLeft > heightRight)
    {
        return FindOptimalMoveHelper(treeNode->next_moves[LEFT], list, currentPlayer);
    }

    else //None is NULL and they are the same length - We activate the rule from page 2 NEW
    {
        switch (currentPlayer)
        {
            case 'T':
                return FindOptimalMoveHelper(treeNode->next_moves[LEFT], list, currentPlayer); //CHANGED T->goes highest //True because T is upsideDown

            case 'B':
                return FindOptimalMoveHelper(treeNode->next_moves[LEFT], list, currentPlayer); //CHANGED B-> goes lowest
        }
    }
}

/*Input: A pointer to a SingleSourceMovesList and a pointer to a SingleSourceMovesTreeNode.
Function: This function inserts a new list cell to the end of the list. The list cell is created from the provided treeNode.*/
void insertDataToEndList(SingleSourceMovesList *lst,SingleSourceMovesTreeNode *treeNode)
{
    SingleSourceMovesListCell *newTail;
    newTail = createNewListNode(treeNode, NULL);
    insertNodeToEndList(lst, newTail);
}

/*Input: A pointer to a SingleSourceMovesTreeNode and a pointer to a SingleSourceMovesListCell representing the next node.
Function: This function creates a new SingleSourceMovesListCell from a SingleSourceMovesTreeNode.
Return: Returns a pointer to the newly created SingleSourceMovesListCell.*/
SingleSourceMovesListCell* createNewListNode(SingleSourceMovesTreeNode *treeNode, SingleSourceMovesListCell *next)
{
    SingleSourceMovesListCell * res;

    res = (SingleSourceMovesListCell*) malloc (sizeof(SingleSourceMovesListCell));
    checkMemoryAllocation(res);

    res->captures = treeNode->total_captures_so_far;
    res->position = treeNode->pos;
    res->next = next;

    return res;
}

/*Input: This function takes a pointer to a SingleSourceMovesList and a pointer to a SingleSourceMovesListCell.
Function: This function inserts a new node (represented by SingleSourceMovesListCell) at the end of the given list (SingleSourceMovesList). If the list is empty, the new node becomes the head and the tail of the list. If the list is not empty, the new node is added to the end of the list, and the tail of the list is updated to point to the new node.
Return: modifies the SingleSourceMovesList in-place.*/
void insertNodeToEndList(SingleSourceMovesList * lst, SingleSourceMovesListCell *tail)
{
    if (lst == NULL)
        return;

    if (isEmptyList(lst) == true)
        lst->head = lst->tail = tail;

    else
    {
        lst->tail->next = tail;
        lst->tail = tail;
    }
    tail->next = NULL;
}

//Question3

//Input: A Board data structure representing the game state, and a Player enum representing the current player.
//Function: This function computes all the possible moves for a given player in the given board state. It iterates over each board square, checks if the player can move from that square, and if so, it computes the optimal move from that square and adds it to the player's moves list.
//Return: Returns a pointer to a MultipleSourceMovesList that contains all the optimal moves for the given player.
MultipleSourceMovesList *FindAllPossiblePlayerMoves(Board board, Player player)
{
    MultipleSourceMovesList *currentPlayerMovesList;

    checkersPos *src;
    src = (checkersPos *) malloc(sizeof (checkersPos));
    checkMemoryAllocationPos(src);


    currentPlayerMovesList = (MultipleSourceMovesList *) malloc (sizeof (MultipleSourceMovesList));
    makeEmptyMultiList(currentPlayerMovesList);

    checkMemoryAllocationList(currentPlayerMovesList);

    SingleSourceMovesTree *sourceMovesTree;

    for(int i = 0; i < BOARD_SIZE; i++)
    {
        src->row = i + 'A';
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            src->col = j + '1';

            if(board[i][j] == player)
            {
                sourceMovesTree = FindSingleSourceMoves(board, src);

                if (sourceMovesTree->source->next_moves[0] == NULL && sourceMovesTree->source->next_moves[1] == NULL)
                {
                    continue;
                }
                SingleSourceMovesList *singleList = FindSingleSourceOptimalMove(sourceMovesTree);
                freeTree(sourceMovesTree);


                MultipleSourceMovesListCell* newList = createNewMultiListNode(singleList, NULL);

                insertNodeToEndMultiList(currentPlayerMovesList, newList);
            }
        }
    }
    return currentPlayerMovesList;
}



//Input: A pointer to a SingleSourceMovesList and a pointer to the next MultipleSourceMovesListCell.
//Function: This function creates a new MultipleSourceMovesListCell that contains the given list and points to the given next cell.
//Return: Returns a pointer to the newly created MultipleSourceMovesListCell.
MultipleSourceMovesListCell *createNewMultiListNode(SingleSourceMovesList *insertedList, MultipleSourceMovesListCell *next)
{
    MultipleSourceMovesListCell * res;

    res = (MultipleSourceMovesListCell*) malloc (sizeof(MultipleSourceMovesListCell));
    checkMemoryAllocation(res);

    res->single_source_moves_list = insertedList;
    res->next = next;

    return res;
}

void insertNodeToEndMultiList(MultipleSourceMovesList* lst, MultipleSourceMovesListCell *newTail)
{
    if (isEmptyMultiList(lst) == true)
        lst->head = lst->tail = newTail;

    else
    {
        lst->tail->next = newTail;
        lst->tail = newTail;
    }
    newTail->next = NULL;
}

//Input: A pointer to a SingleSourceMovesList.
//Function: This function initializes the provided list to an empty state.
void makeEmptyList(SingleSourceMovesList *lst)
{
    lst->head = NULL;
    lst->tail = NULL;
}

void makeEmptyMultiList(MultipleSourceMovesList *lst)
{
    lst->head= NULL;
    lst->tail = NULL;
}

//Input: A pointer to a SingleSourceMovesList.
//Function: This function checks if the provided list is empty or not.
//Return: Returns a boolean, true if the list is empty, false otherwise.
bool isEmptyList(SingleSourceMovesList * lst)
{
    if (lst->head == NULL)
        return true;
    else
        return false;
}

//Input: A pointer to a MultipleSourceMovesList.
//Function: This function checks if the provided list is empty or not.
//Return: Returns a boolean, true if the list is empty, false otherwise.
bool isEmptyMultiList(MultipleSourceMovesList *lst)
{
    if (lst->head == NULL)
        return true;
    else
        return false;
}

//This function checks if the allocation was successful.
void checkMemoryAllocation(SingleSourceMovesListCell * listCell)
{
    if (listCell == NULL)
    {
        printf("Memory allocation error!!!\n");
        exit(1);
    }
}

//This function checks if the allocation was successful.
void checkMemoryAllocationList(SingleSourceMovesList * listCell)
{
    if (listCell == NULL)
    {
        printf("Memory allocation error!!!\n");
        exit(1);
    }
}

//Input: A pointer to a MultipleSourceMovesListCell.
//Function: This function frees the memory occupied by the given MultipleSourceMovesListCell.
void freeMultipleSourceMovesListCell(MultipleSourceMovesListCell *node)
{
    free(node->single_source_moves_list);
    free(node);
}

//Input: A pointer to a MultipleSourceMovesListList.
//Function: This function frees the memory occupied by the given MultipleSourceMovesListCell.
void freeMultipleSourceMovesList(MultipleSourceMovesList* lst)
{
    MultipleSourceMovesListCell *curr = lst->head;
    MultipleSourceMovesListCell *next = NULL;
    while (curr != NULL)
    {
        next = curr->next;
        freeMultipleSourceMovesListCell(curr);
        curr = next;
    }
}

/*Input: A pointer to a SingleSourceMovesListCell.
Function: This function frees the memory occupied by the given MultipleSourceMovesListCell.*/
void freeSingleSourceMovesListCell(SingleSourceMovesListCell *node)
{
    free(node->position);
    free(node);
}

/*Input: A pointer to a SingleSourceMovesList.
Function: This function frees the memory occupied by the given MultipleSourceMovesListCell.*/
void freeSingleSourceMovesList(SingleSourceMovesList* lst)
{
    SingleSourceMovesListCell *curr = lst->head;
    SingleSourceMovesListCell *next = NULL;

    while (curr != NULL)
    {
        next = curr->next;
        freeSingleSourceMovesListCell(curr);
        curr = next;
    }
}


//Debugging
void printMultiList(MultipleSourceMovesList *MList)
{
    MultipleSourceMovesListCell* curr = MList->head;

    while (curr != NULL)
    {
        printList(curr->single_source_moves_list);
        printf("\n");
        curr = curr->next;

    }
    printf("\n");
}


void printList(SingleSourceMovesList *list)
{
    SingleSourceMovesListCell* res;
    res = list->head;

    while (res != NULL)
    {
        printf("%c%c <> %d", res->position->row ,res->position->col, res->captures );
        res = res->next;
    }
}