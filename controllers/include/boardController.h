#ifndef BOARDCONTROLLER_H
#define BOARDCONTROLLER_H

#include "raylib.h"
#include "math.h"

#include "cellController.h"

#define COLS 10
#define ROWS 10
#define MINE_PROB 0.1

typedef struct Board
{
    Cell *grid[COLS][ROWS];
    int boardWidth;
    int boardHeight;
    Vector2 bPos;
    int cellWidth;
    int cellHeight;
    int nMines;
    int nCorrectRevealed;
} Board;

Board *BoardCreate(void);
void BoardRestart(Board *board);
bool BoardRevealCell(Board *board, Vector2 mPos);
void BoardRevealCellNeighbors(Board *board, Cell *cell);
void BoardAlternateFlag(Board *board, Vector2 mPos);
bool BoardIsCorrect(Board *board);

#endif