#include <raylib.h>

#include "config.h"
#include "game.h"
#include "player.h"
#include "asteroid.h"

void Game_Run(void){
  Player player;
  AsteroidManager manager;

  Player_Init(&player);
  manager = Asteroid_CreateManager();

  unsigned int framesCounter = 0;

  Vector2 borders = (Vector2){SCREEN_WIDTH, SCREEN_HEIGHT};

  while (!WindowShouldClose()) {
    framesCounter++;

    float dt = GetFrameTime();
    int score = (int)GetTime();

    Player_Update(&player, dt, borders);

    if (framesCounter % 120 == 0) {
      if (Asteroid_Add(
        &manager,
        DARKGRAY,
        ASTEROID_CIRCLE,
        35,
        35,
        250,
        1,
        1,
        10
      )) {

        Asteroid_Spawn(
          &manager.data[manager.count - 1],
          Player_GetPosition(&player)
        );
      }
    }

    Asteroid_UpdateAll(&manager, dt);

    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText("WASD / HJKL / Arrows", 20, 20, 20, BLACK);
    DrawText(TextFormat("Score: %d", score), 20, 50, 20, BLACK);

    Player_Draw(&player);
    Asteroid_DrawAll(&manager);

    EndDrawing();
  }
  Asteroid_DestroyManager(&manager);
}