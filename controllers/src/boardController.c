#include "boardController.h"

typedef struct Vector2Index
{
    int i;
    int j;
} Vector2Index;

static void BoardInit(Board *board);
static void BoardInitCellMinesAround(Board *board);
static void BoardInitGrid(Board *this);
static Vector2Index BoardGetIndexes(Board *this, Vector2 mPos);
static bool IsInBoard(int i, int j);

Board *
BoardCreate(void)
{
    Board *board = malloc(sizeof(Board));
    BoardInit(board);

    return board;
}

static void BoardInit(Board *board)
{
    int boardHeight = GetScreenHeight() - 100;
    int boardWidth = GetScreenWidth();

    board->boardHeight = boardHeight;
    board->boardWidth = boardWidth;
    board->cellHeight = boardHeight / ROWS;
    board->cellWidth = boardWidth / COLS;
    board->bPos = (Vector2){.x = 0, .y = 100};

    BoardInitGrid(board);
}

void BoardRestart(Board *this)
{
    BoardInitGrid(this);
}

static void BoardInitGrid(Board *this)
{
    this->nCorrectRevealed = 0;
    this->nMines = 0;
    for (int i = 0; i < COLS; i++)
    {
        for (int j = 0; j < ROWS; j++)
        {
            bool isMine = false;
            if (rand() < MINE_PROB * RAND_MAX)
            {
                isMine = true;
                this->nMines++;
            }

            this->grid[i][j] = CellCreate(i, j, isMine);
        }
    }

    BoardInitCellMinesAround(this);
}

static void BoardInitCellMinesAround(Board *this)
{

    for (int i = 0; i < COLS; i++)
    {
        for (int j = 0; j < ROWS; j++)
        {
            if (CellContainMine(this->grid[i][j]))
            {
                int iiFirst = fmax(0, i - 1);
                int jjFirst = fmax(0, j - 1);
                int iiLast = fmin(COLS - 1, i + 1);
                int jjLast = fmin(ROWS - 1, j + 1);
                for (int ii = iiFirst; ii <= iiLast; ii++)
                {
                    for (int jj = jjFirst; jj <= jjLast; jj++)
                    {
                        Cell *cellToReveal = this->grid[ii][jj];
                        if (!CellContainMine(cellToReveal))
                        {
                            int newAroundMines = CellGetAroundMines(cellToReveal) + 1;
                            CellSetAroundMines(cellToReveal, newAroundMines);
                        }
                    }
                }
            }
        }
    }
}

bool BoardRevealCell(Board *this, Vector2 mPos)
{

    Vector2Index indexes = BoardGetIndexes(this, mPos);
    int i = indexes.i;
    int j = indexes.j;
    if (IsInBoard(i, j))
    {
        Cell *cellToReveal = this->grid[i][j];

        CellReveal(cellToReveal);

        if (CellGetAroundMines(cellToReveal) == 0)
        {
            BoardRevealCellNeighbors(this, cellToReveal);
        }

        if (CellContainMine(cellToReveal))
        {
            return true;
        }

        this->nCorrectRevealed++;
    }

    return false;
}

void BoardRevealCellNeighbors(Board *this, Cell *cell)
{
    if (CellGetAroundMines(cell) != 0 || CellContainMine(cell))
    {
        return;
    }

    int iiFirst = fmax(0, cell->i - 1);
    int jjFirst = fmax(0, cell->j - 1);
    int iiLast = fmin(COLS - 1, cell->i + 1);
    int jjLast = fmin(ROWS - 1, cell->j + 1);
    for (int ii = iiFirst; ii <= iiLast; ii++)
    {
        for (int jj = jjFirst; jj <= jjLast; jj++)
        {
            if (!CellContainMine(this->grid[ii][jj]) && !CellIsRevealed(this->grid[ii][jj]))
            {
                CellReveal(this->grid[ii][jj]);
                this->nCorrectRevealed++;
                BoardRevealCellNeighbors(this, this->grid[ii][jj]);
            }
        }
    }
}

void BoardAlternateFlag(Board *this, Vector2 mPos)
{

    Vector2Index indexes = BoardGetIndexes(this, mPos);
    int i = indexes.i;
    int j = indexes.j;

    if (IsInBoard(i, j))
    {
        Cell *cellToAlternate = this->grid[i][j];
        CellAlternateFlag(cellToAlternate);
    }
}

static Vector2Index BoardGetIndexes(Board *this, Vector2 mPos)
{
    Vector2Index indexes = {
        .i = (mPos.x - this->bPos.x) / this->cellWidth,
        .j = (mPos.y - this->bPos.y) / this->cellHeight};
    return indexes;
}

bool BoardIsCorrect(Board *this)
{
    if (this->nMines + this->nCorrectRevealed == COLS * ROWS)
    {
        return true;
    }
    return false;
}

int GetBoardCols(void)
{
    return COLS;
}

int GetBoardRows(void)
{
    return ROWS;
}

static bool IsInBoard(int i, int j)
{
    return (i >= 0 && i < COLS) && (j >= 0 && j < ROWS);
}
