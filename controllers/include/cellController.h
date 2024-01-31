#ifndef CELLCONTROLLER_H
#define CELLCONTROLLER_H

#include "raylib.h"

#include <stdlib.h>

typedef struct
{
    int i;
    int j;
    bool containMine;
    bool revealed;
    bool flagged;
    int aroundMines;
} Cell;

Cell *CellCreate(int i, int j, bool isMine);
void CellReveal(Cell *cell);
void CellAlternateFlag(Cell *cell);
int CellGetAroundMines(Cell *cell);
void CellSetAroundMines(Cell *cell, int aroundMines);
bool CellContainMine(Cell *cell);
bool CellIsRevealed(Cell *cell);

#endif