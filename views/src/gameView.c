#include "gameView.h"

void GameDrawCorrect(Game *game);

void GameDraw(Game *game)
{
    GameDrawCorrect(game);
    BoardDraw(game->board);

    if (game->state == LOSE)
    {
        DrawRectangle(0, 0, game->screenWidth, game->screenHeight, BG_COLOR_LOSE);
        char str[21] = "Press 'R' to restart";
        Vector2 textSize = MeasureTextEx(GetFontDefault(), str, 25, 0.8);
        DrawText(str, (game->screenWidth - textSize.x) / 2, (game->screenHeight - textSize.y) / 2, 25, WHITE);
    }
    else if (game->state == WIN)
    {
        DrawRectangle(0, 0, game->screenWidth, game->screenHeight, BG_COLOR_LOSE);
        char str[30] = "YOU WIN!\nPress 'R' to restart";
        Vector2 textSize = MeasureTextEx(GetFontDefault(), str, 25, 0.8);
        DrawText(str, (game->screenWidth - textSize.x) / 2, (game->screenHeight - textSize.y) / 2, 25, WHITE);
    }
}

void GameDrawCorrect(Game *game)
{
    char str[11];
    sprintf(str, "Score: %i", game->board->nCorrectRevealed);
    DrawText(str, 0, 0, 30, BLACK);
}