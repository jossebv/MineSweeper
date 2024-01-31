#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "raylib.h"

#include "boardController.h"

typedef enum
{
    PLAY = 0,
    LOSE,
    WIN
} GAME_STATES;

typedef struct Game
{
    GAME_STATES state;
    Board *board;
    int screenWidth;
    int screenHeight;
} Game;

Game *GameCreate(void);
void GameInit(Game *this);
void GameRestart(Game *this);
void GameUpdate(Game *this);
void GameLose(Game *this);
void GameCheckWin(Game *this);

#endif