
#include "list.h"
#include "general.h" //NEW

//Question 2
SingleSourceMovesList *FindSingleSourceOptimalMove(SingleSourceMovesTree *moves_tree)
{
    Player currentPlayer = findCurrentPlayer(moves_tree->source->board, moves_tree->source->pos); //NEW

    SingleSourceMovesList *optimalMoveList;

    optimalMoveList = (SingleSourceMovesList*) malloc(sizeof (SingleSourceMovesList));
    checkMemoryAllocationList(optimalMoveList);

    makeEmptyList(optimalMoveList);

    FindOptimalMoveHelper(moves_tree->source,optimalMoveList, currentPlayer);

    return optimalMoveList;
    //Free tree
}

void FindOptimalMoveHelper(SingleSourceMovesTreeNode *treeNode ,SingleSourceMovesList *list ,Player currentPlayer) //Changed
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
        return FindOptimalMoveHelper(treeNode->next_moves[RIGHT], list, currentPlayer); //CHANGED

    else if (treeNode->next_moves[RIGHT] == NULL)
        return FindOptimalMoveHelper(treeNode->next_moves[LEFT], list, currentPlayer); //CHANGED


    heightLeft = heightHelper(treeNode->next_moves[LEFT]);
    heightRight = heightHelper(treeNode->next_moves[RIGHT]);

    if (heightRight > heightLeft)
    {
        return FindOptimalMoveHelper(treeNode->next_moves[RIGHT], list, currentPlayer); //CHANGED
    }

    if (heightLeft > heightRight) //Changed < to >
    {
        return FindOptimalMoveHelper(treeNode->next_moves[LEFT], list, currentPlayer); //CHANGED
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


///Single
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

            if(board[i][j] == player)
            {
                sourceMovesTree = FindSingleSourceMoves(board, src);
                //countPlayersPieces++;
                if (sourceMovesTree->source->next_moves[0] == NULL && sourceMovesTree->source->next_moves[1] == NULL)
                {
                    continue;
                }
                SingleSourceMovesList *singleList = FindSingleSourceOptimalMove(sourceMovesTree);
                freeTree(sourceMovesTree);


                MultipleSourceMovesListCell* newList = createNewMultiListNode(singleList, NULL);
                //insertListToEndMultiList(&currentPlayerMovesList, singleList);
                //insertListToEndMultiList(currentPlayerMovesList,singleList);

                insertNodeToEndMultiList(currentPlayerMovesList, newList);
            }
        }
    }
    //currentPlayerMovesList = realloc(currentPlayerMovesList,  sizeof(MultipleSourceMovesList*) * countPlayersPieces);
    //add free position
    return currentPlayerMovesList; //Free list in main
}

///////Multi
void insertListToEndMultiList(MultipleSourceMovesList **dest, SingleSourceMovesList *inserted)
{
    MultipleSourceMovesListCell *newTail;
    newTail = createNewMultiListNode(inserted, NULL);
    insertNodeToEndMultiList(dest, newTail);
}

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

