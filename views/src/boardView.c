#include "boardView.h"

void BoardDraw(Board *board)
{
    for (int i = 0; i < COLS; i++)
    {
        for (int j = 0; j < ROWS; j++)
        {
            CellDraw(board->grid[i][j], board->cellWidth, board->cellHeight, board->bPos);
        }
    }
}