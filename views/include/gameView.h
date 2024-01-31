#include "raylib.h"

#include <stdio.h>

#include "boardView.h"
#include "gameController.h"

#define BG_COLOR_LOSE \
    (Color) { 54, 54, 54, 69 }

void GameDraw(Game *game);