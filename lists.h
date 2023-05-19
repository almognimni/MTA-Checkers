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

#endif
