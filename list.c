
#include "list.h"

//Question 2
SingleSourceMovesList *FindSingleSourceOptimalMove(SingleSourceMovesTree *moves_tree)
{
    //char player;
    SingleSourceMovesList *optimalMoveList;

    optimalMoveList = (SingleSourceMovesList*) malloc(sizeof (SingleSourceMovesList));
    checkMemoryAllocationList(optimalMoveList);

    makeEmptyList(optimalMoveList);

    FindOptimalMoveHelper(moves_tree->source,optimalMoveList);

    return optimalMoveList;
    //Free tree
}

void FindOptimalMoveHelper(SingleSourceMovesTreeNode *treeNode ,SingleSourceMovesList *list)
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
        return FindOptimalMoveHelper(treeNode->next_moves[RIGHT], list);

    else if (treeNode->next_moves[RIGHT] == NULL)
        return FindOptimalMoveHelper(treeNode->next_moves[LEFT], list);


    heightLeft = heightHelper(treeNode->next_moves[LEFT]);
    heightRight = heightHelper(treeNode->next_moves[RIGHT]);

    if (heightRight > heightLeft)
    {
        return FindOptimalMoveHelper(treeNode->next_moves[RIGHT], list);
    }

    if (heightLeft < heightRight)
    {
        return FindOptimalMoveHelper(treeNode->next_moves[LEFT], list);
    }

    else
    {
        if ((treeNode->next_moves[RIGHT] != NULL && treeNode->next_moves[RIGHT]->pos->col) < (treeNode->next_moves[LEFT] != NULL && treeNode->next_moves[LEFT]->pos->col))
        {
            return FindOptimalMoveHelper(treeNode->next_moves[RIGHT], list);
        }
        else
        {
            return FindOptimalMoveHelper(treeNode->next_moves[LEFT], list);
        }
    }
}


//Question3
MultipleSourceMovesList *FindAllPossiblePlayerMoves(Board board, Player player)
{
    MultipleSourceMovesList *currentPlayerMovesList;

    checkersPos *src;
    src = (checkersPos *) malloc(sizeof (checkersPos));
    checkMemoryAllocationPos(src);

    //int countPlayersPieces = 0;

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
            sourceMovesTree = FindSingleSourceMoves(board, src);

            if(board[i][j] == player)
            {
                insertDataToEndList2(currentPlayerMovesList,FindSingleSourceOptimalMove(sourceMovesTree) );
            }
        }
    }
    //currentPlayerMovesList = realloc(currentPlayerMovesList,  sizeof(MultipleSourceMovesList*) * countPlayersPieces);
    //add free position
    return currentPlayerMovesList; //Free list in main

}

void insertDataToEndList(SingleSourceMovesList *lst,SingleSourceMovesTreeNode *treeNode)
{
    SingleSourceMovesListCell *newTail;
    newTail = createNewListNode(treeNode, NULL);
    insertNodeToEndList(lst, newTail);
}

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

void insertListToEndMultiList(MultipleSourceMovesList **dest, SingleSourceMovesList *inserted)
{
    MultipleSourceMovesListCell *newTail;
    newTail = createNewMultiListNode(inserted, NULL);
    insertNodeToEndMultiList(dest, newTail);
}

MultipleSourceMovesListCell *createNewListNode2(SingleSourceMovesList *insertedList, MultipleSourceMovesListCell *next)
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
    if (isEmptyList(lst) == true)
        lst->head = lst->tail = newTail;

    else
    {
        lst->tail->next = newTail;
        lst->tail = newTail;
    }
    newTail->next = NULL;
}

void printList(SingleSourceMovesList *list)
{
    SingleSourceMovesListCell* res;
    res = list->head;

    while (res != NULL)
    {
        printf("%c%c <> %d \n", res->position->row ,res->position->col, res->captures );
        res = res->next;
    }
}

void printMultiList(MultipleSourceMovesList *MList)
{
    MultipleSourceMovesListCell* curr = MList->head;

    while (curr != NULL)
    {
        printList(curr->single_source_moves_list);
        curr = curr->next;
    }
}

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

bool isEmptyList(SingleSourceMovesList * lst)
{
    if (lst->head == NULL)
        return true;
    else
        return false;
}

bool isEmptyMultiList(MultipleSourceMovesList *lst)
{
    if (lst->head == NULL)
        return true;
    else
        return false;
}

void checkMemoryAllocation(SingleSourceMovesListCell * listCell)
{
    if (listCell == NULL)
    {
        printf("Memory allocation error!!!\n");
        exit(1);
    }
}

void checkMemoryAllocationList(SingleSourceMovesList * listCell)
{
    if (listCell == NULL)
    {
        printf("Memory allocation error!!!\n");
        exit(1);
    }
}