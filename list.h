#ifndef PROJECT_LISTS_H
#define PROJECT_LISTS_H

#include "board.h"
#include "tree.h"

/*Definitions*/

/*Single list*/
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


/*Multiple source lists*/
typedef struct _multipleSourceMovesListCell
{
    SingleSourceMovesList *single_source_moves_list;
    struct _multipleSourceMovesListCell *next;
}MultipleSourceMovesListCell;

typedef struct _multipleSourceMovesList
{
    MultipleSourceMovesListCell *head;
    MultipleSourceMovesListCell *tail;

}MultipleSourceMovesList;

/*Functions*/

/*Single source functions */
//Question 2
SingleSourceMovesList *FindSingleSourceOptimalMove(SingleSourceMovesTree *moves_tree);
void FindOptimalMoveHelper(SingleSourceMovesTreeNode *treeNode ,SingleSourceMovesList *list ,Player currentPlayer);

SingleSourceMovesListCell *createNewListNode(SingleSourceMovesTreeNode *treeNode, SingleSourceMovesListCell *next);
void insertDataToEndList(SingleSourceMovesList *lst,SingleSourceMovesTreeNode *treeNode);
void insertNodeToEndList(SingleSourceMovesList * lst, SingleSourceMovesListCell *tail);

bool isEmptyList(SingleSourceMovesList * lst);
void makeEmptyList(SingleSourceMovesList *lst);

void checkMemoryAllocation(SingleSourceMovesListCell * listCell);
void checkMemoryAllocationList(SingleSourceMovesList * listCell);

//Question3
/*Multiple source lists*/
MultipleSourceMovesList *FindAllPossiblePlayerMoves(Board board, Player player);

void makeEmptyMultiList(MultipleSourceMovesList *lst);
bool isEmptyMultiList(MultipleSourceMovesList *lst);

MultipleSourceMovesListCell *createNewMultiListNode(SingleSourceMovesList *listCell, MultipleSourceMovesListCell *next);
void insertNodeToEndMultiList(MultipleSourceMovesList* lst, MultipleSourceMovesListCell *newTail);

/*For debugging*/
void printList(SingleSourceMovesList *list);
void printMultiList(MultipleSourceMovesList *MList);


#endif
