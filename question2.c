#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BOARD_SIZE 8
#define LEFT 0
#define RIGHT 1

typedef unsigned char Board [BOARD_SIZE][BOARD_SIZE];
typedef unsigned char Player;

typedef struct _checkersPos
{
    char row,col;
}checkersPos;

typedef struct _SingleSourceMovesTreeNode
{
    Board board;
    checkersPos *pos;
    unsigned short total_captures_so_far;
    struct _SingleSourceMovesTreeNode *next_moves[2];

}SingleSourceMovesTreeNode;

typedef struct _SingleSourceMovesTree
{
    SingleSourceMovesTreeNode *source;
}SingleSourceMovesTree;


////////////////////////
typedef struct _SingleSourceMovesListCell
{
    checkersPos *position;
    unsigned short captures;
    struct _SingleSourceMovesListCell *next;

}SingleSourceMovesListCell;

typedef struct _SingleSourceMovesList
{
    SingleSourceMovesListCell *head;
    SingleSourceMovesListCell *tail;
}SingleSourceMovesList;

////////////////////////////
SingleSourceMovesList *FindSingleSourceOptimalMove(SingleSourceMovesTree *moves_tree);
int max(int a, int b);
SingleSourceMovesListCell* FindOptimalMoveHelper(SingleSourceMovesTreeNode *treeNode ,SingleSourceMovesList *list);
int heightHelper(SingleSourceMovesTreeNode *root);
int height(SingleSourceMovesTree *tr);
void makeEmptyList(SingleSourceMovesList *lst);
void checkMemoryAllocation(SingleSourceMovesListCell * listCell);
void checkMemoryAllocationList(SingleSourceMovesList * listCell);


//SingleSourceMovesListCell * createNewListNode(int data, SingleSourceMovesListCell * next);
SingleSourceMovesListCell *createNewListNode(SingleSourceMovesTreeNode *treeNode, SingleSourceMovesListCell *next);
void insertDataToEndList(SingleSourceMovesList *lst,SingleSourceMovesTreeNode *treeNode);
void insertNodeToEndList(SingleSourceMovesList * lst, SingleSourceMovesListCell *tail);
bool isEmptyList(SingleSourceMovesList * lst);

int main()
{

}



SingleSourceMovesList *FindSingleSourceOptimalMove(SingleSourceMovesTree *moves_tree)
{
    //int currLevel = 0;
    int highestLevel = height(moves_tree->source);

    //char player;
    SingleSourceMovesList *optimalMoveList;

    optimalMoveList = (SingleSourceMovesList*) malloc(sizeof (SingleSourceMovesList));
    checkMemoryAllocationList(optimalMoveList);

    makeEmptyList(optimalMoveList);

    //optimalMoveList->head = createNewListNode(moves_tree->source, NULL);

    FindOptimalMoveHelper(moves_tree->source,optimalMoveList);

    //Free tree

}

SingleSourceMovesListCell* FindOptimalMoveHelper(SingleSourceMovesTreeNode *treeNode ,SingleSourceMovesList *list)
{
    int heightRight, heightLeft;

    if (treeNode == NULL)
    {
        return NULL;
    }

    insertDataToEndList(list, treeNode);

    heightLeft = heightHelper(treeNode->next_moves[LEFT]);
    heightRight = heightHelper(treeNode->next_moves[RIGHT]);

    if (heightRight > heightLeft)
    {
        return FindOptimalMoveHelper(treeNode->next_moves[RIGHT], list);
    }

    if (heightLeft < heightRight)
    {
        return FindOptimalMoveHelper(treeNode->next_moves[RIGHT], list);
    }

    else
    {
        if ((treeNode->next_moves[RIGHT]->pos->col) < (treeNode->next_moves[LEFT]->pos->col))
        {
            return FindOptimalMoveHelper(treeNode->next_moves[RIGHT], list);
        }
        else
        {
            return FindOptimalMoveHelper(treeNode->next_moves[LEFT], list);
        }
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
        heightLeft = heightHelper(root->next_moves[LEFT]);
        heightRight = heightHelper(root->next_moves[RIGHT]);
        return 1 + max(heightLeft, heightRight);
    }
}

int max(int a, int b)
{
    return a > b ? a : b;
}

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
        printf("%c%c <> %d ", res->position->row ,res->position->col, res->captures );
        res = res->next;
    }
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
