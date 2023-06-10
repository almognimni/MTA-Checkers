#ifndef PROJECT_LISTS_H
#define PROJECT_LISTS_H

#include "board.h"
#include "tree.h"

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

//_____________________________________________

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
SingleSourceMovesList *FindSingleSourceOptimalMove(SingleSourceMovesTree *moves_tree);

MultipleSourceMovesList *FindAllPossiblePlayerMoves(Board board, Player player);

void makeEmptyList(SingleSourceMovesList *lst);
void checkMemoryAllocation(SingleSourceMovesListCell * listCell);
void checkMemoryAllocationList(SingleSourceMovesList * listCell);

SingleSourceMovesListCell *createNewListNode(SingleSourceMovesTreeNode *treeNode, SingleSourceMovesListCell *next);
void insertDataToEndList(SingleSourceMovesList *lst,SingleSourceMovesTreeNode *treeNode);
void insertNodeToEndList(SingleSourceMovesList * lst, SingleSourceMovesListCell *tail);
bool isEmptyList(SingleSourceMovesList * lst);
void printList(SingleSourceMovesList *list);

SingleSourceMovesList *FindSingleSourceOptimalMove(SingleSourceMovesTree *moves_tree);
//void FindOptimalMoveHelper(SingleSourceMovesTreeNode *treeNode ,SingleSourceMovesList *list);
void FindOptimalMoveHelper(SingleSourceMovesTreeNode *treeNode ,SingleSourceMovesList *list ,Player currentPlayer); //Changed
void printMultiList(MultipleSourceMovesList *MList);

void makeEmptyMultiList(MultipleSourceMovesList *lst);
bool isEmptyMultiList(MultipleSourceMovesList *lst);

void insertListToEndMultiList(MultipleSourceMovesList **dest, SingleSourceMovesList *inserted);
MultipleSourceMovesListCell *createNewMultiListNode(SingleSourceMovesList *listCell, MultipleSourceMovesListCell *next);
void insertNodeToEndMultiList(MultipleSourceMovesList* lst, MultipleSourceMovesListCell *newTail);
#endif
