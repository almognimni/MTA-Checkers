
#include "lists.h"

void makeEmptyList(SingleSourceMovesList *lst)
{
    lst->head = NULL;
    lst->tail = NULL;
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

void insertDataToEndList(SingleSourceMovesList *lst,SingleSourceMovesTreeNode *treeNode)
{
    SingleSourceMovesListCell *newTail;
    newTail = createNewListNode(treeNode, NULL);
    insertNodeToEndList(lst, newTail);
}

void insertNodeToEndList(SingleSourceMovesList * lst, SingleSourceMovesListCell *tail)
{
    if (isEmptyList(lst) == true)
        lst->head = lst->tail = tail;

    else
    {
        lst->tail->next = tail;
        lst->tail = tail;
    }
    tail->next = NULL;
}

bool isEmptyList(SingleSourceMovesList * lst)
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

MultipleSourceMovesList *FindAllPossiblePlayerMoves(Board board, Player player)
{
    MultipleSourceMovesList **currentPlayerMovesList;
    checkersPos *src;

    int countPlayersPieces = 0;

    currentPlayerMovesList = (MultipleSourceMovesList **) malloc (sizeof (MultipleSourceMovesList *) * STARTING_PIECES);
    checkMemoryAllocationList(currentPlayerMovesList);

    SingleSourceMovesTree *sourceMovesTree;

    for(int i = 0; i < BOARD_SIZE; i++)
    {
        src->row = i;
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            src->col = j;
            sourceMovesTree = FindSingleSourceMoves(board, src);

            if('B' == player)
            {
                currentPlayerMovesList[countPlayersPieces]->head = FindSingleSourceOptimalMove(sourceMovesTree);
                countPlayersPieces++;
            }

        }
    }
    currentPlayerMovesList = realloc(currentPlayerMovesList, countPlayersPieces);
    return currentPlayerMovesList; //Free list int main

}

//
//void freeNode(SingleSourceMovesListCell* node)
//{
//    free(node->dataPtr);
//    free(node);
//}
//
//void freeList(SingleSourceMovesList* lst)
//{
//    SingleSourceMovesListCell *curr = lst->head;
//    SingleSourceMovesListCell *next = NULL;
//    while (curr != NULL)
//    {
//        next = curr->next;
//        freeNode(curr);
//        curr = next;
//    }
//}