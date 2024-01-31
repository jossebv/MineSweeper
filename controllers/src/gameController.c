#include "gameController.h"

Game *GameCreate()
{
    Game *game = malloc(sizeof(Game));

    GameInit(game);

    return game;
}

void GameInit(Game *this)
{
    Board *board = BoardCreate();

    *this = (Game){
        .screenWidth = GetScreenWidth(),
        .screenHeight = GetScreenHeight(),
        .state = PLAY,
        .board = board};
}

void GameRestart(Game *this)
{
    this->state = PLAY;

    BoardRestart(this->board);
}

void GameUpdate(Game *this)
{
    if (this->state == LOSE || this->state == WIN)
    {
        if (IsKeyPressed(KEY_R))
        {
            GameRestart(this);
        }
        return;
    }
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 mPos = GetMousePosition();
        bool containMine = BoardRevealCell(this->board, mPos);
        if (containMine)
        {
            this->state = LOSE;
            return;
        }
    }
    else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
    {
        Vector2 mPos = GetMousePosition();
        BoardAlternateFlag(this->board, mPos);
    }

    GameCheckWin(this);
}

void GameLose(Game *this)
{
    this->state = LOSE;
}

void GameCheckWin(Game *this)
{
    if (BoardIsCorrect(this->board))
    {
        this->state = WIN;
    }
}
