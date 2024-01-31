#include "cellController.h"

static void CellInit(Cell *this, int i, int j, bool isMine);

Cell *CellCreate(int i, int j, bool isMine)
{
    Cell *cell = malloc(sizeof(Cell));
    CellInit(cell, i, j, isMine);
    return cell;
}

static void CellInit(Cell *this, int i, int j, bool isMine)
{

    this->i = i;
    this->j = j;
    this->aroundMines = 0;
    this->containMine = isMine;
    this->flagged = false;
    this->revealed = false;
}

void CellReveal(Cell *this)
{
    if (this->flagged || this->revealed)
    {
        return;
    }
    else if (this->containMine)
    {
        // Loose
        this->revealed = true;
        return;
    }

    this->revealed = true;
}

void CellAlternateFlag(Cell *cell)
{
    cell->flagged = !cell->flagged;
}

int CellGetAroundMines(Cell *this)
{
    return this->aroundMines;
}

void CellSetAroundMines(Cell *this, int aroundMines)
{
    this->aroundMines = aroundMines;
}

bool CellIsRevealed(Cell *this)
{
    return this->revealed;
}

bool CellContainMine(Cell *this)
{
    return this->containMine;
}
