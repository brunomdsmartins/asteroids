#include <raylib.h>

#include "config.h"

#include "game.h"
#include "player.h"

void Game_Run(void) {
  Player player;

  unsigned int framesCounter = 0;

  int score;

  Player_Init(&player);

  while (!WindowShouldClose()) {
    framesCounter++;

    float dt = GetFrameTime();

    if ((framesCounter % 2) == 1) {
      score = GetTime();
      framesCounter = 0;
    }

    Player_Update(&player, dt, (Vector2){SCREEN_WIDTH, SCREEN_HEIGHT});

    BeginDrawing();

    DrawText("Press 'hjkl' to move", (float)SCREEN_WIDTH * 0.05,
             (float)SCREEN_HEIGHT * 0.05, 20, BLACK);

    DrawText(TextFormat("Score: %d", score), (float)SCREEN_WIDTH * 0.05,
             (float)SCREEN_HEIGHT * 0.10, 20, BLACK);

    ClearBackground(RAYWHITE);

    Player_Draw(&player);

    EndDrawing();
  }
}
