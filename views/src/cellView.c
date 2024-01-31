#include "cellView.h"

void CellDraw(Cell *cell, int cellWidth, int cellHeight, Vector2 bPos)
{
    int xPos = cell->i * cellWidth + bPos.x;
    int yPos = cell->j * cellHeight + bPos.y;

    if (cell->revealed)
    {
        if (cell->containMine)
        {
            DrawRectangle(xPos, yPos, cellWidth, cellHeight, RED);
        }
        else
        {
            DrawRectangle(xPos, yPos, cellWidth, cellHeight, GREEN);
            char str[2];
            sprintf(str, "%i", cell->aroundMines);
            Vector2 textSize = MeasureTextEx(GetFontDefault(), str, 25, 0.5);
            DrawText(str, xPos + (cellWidth - textSize.x) / 2, yPos + (cellHeight - textSize.y) / 2, 25, BLACK);
        }
    }
    else if (cell->flagged)
    {
        DrawRectangle(xPos, yPos, cellWidth, cellHeight, YELLOW);
    }

    DrawRectangleLines(xPos, yPos, cellWidth, cellHeight, BLACK);
}