#include <raylib.h>

#include "asteroid.h"
#include "bullet.h"
#include "config.h"
#include "game.h"
#include "main_menu.h"
#include "player.h"
#include "settings_menu.h"

void Game_Run(void) {
  GameState state = GAME_STATE_MENU;
  Player player;
  Menu menu;
  Settings settings;
  BulletManager bullet_manager;
  AsteroidManager asteroid_manager;

  Player_Init(&player);
  Menu_Init(&menu);
  Settings_Init(&settings);
  BulletManager_Init(&bullet_manager);

  asteroid_manager = Asteroid_CreateManager();

  unsigned int framesCounter = 0;
  Vector2 borders = (Vector2){SCREEN_WIDTH, SCREEN_HEIGHT};

  while (!WindowShouldClose() && state != GAME_STATE_EXIT) {
    float dt = GetFrameTime();
    int score = (int)GetTime();

    switch (state) {
    case GAME_STATE_MENU: {
      Menu_Update(&menu);

      MenuAction action = Menu_GetAction(&menu);

      if (action == ACTION_PLAY) {
        state = GAME_STATE_PLAYING;
      } else if (action == ACTION_SETTINGS) {
        state = GAME_STATE_SETTINGS;
      } else if (action == ACTION_EXIT) {
        state = GAME_STATE_EXIT;
      }

      BeginDrawing();
      ClearBackground(RAYWHITE);
      Menu_Draw(&menu);
      EndDrawing();
    } break;
    case GAME_STATE_PLAYING: {
      if (framesCounter % 120 == 0) {
        if (Asteroid_Add(&asteroid_manager, DARKGRAY, ASTEROID_CIRCLE, 35, 35,
                         250, 1, 1, 10)) {

          Asteroid_Spawn(&asteroid_manager.data[asteroid_manager.count - 1],
                         Player_GetPosition(&player));
        }
      }

      if (IsKeyPressed(KEY_SPACE)) {
        BulletManager_Spawn(&bullet_manager, Player_GetPosition(&player),
                            player.rotation);
      }

      BulletManager_Update(&bullet_manager, dt, borders);
      Player_Update(&player, dt, borders);
      Asteroid_UpdateAll(&asteroid_manager, dt);

      BeginDrawing();
      ClearBackground(RAYWHITE);

      DrawText(GetLayoutText(Settings_GetLayout(&settings)), 20, 20, 20, BLACK);
      DrawText(TextFormat("Score: %d", score), 20, 50, 20, BLACK);

      Player_Draw(&player);
      BulletManager_Draw(&bullet_manager);
      Asteroid_DrawAll(&asteroid_manager);

      EndDrawing();
    } break;
    case GAME_STATE_SETTINGS: {
      Settings_Update(&settings);

      bool go_back = Settings_GoBack(&settings);

      if (go_back == true) {
        state = GAME_STATE_MENU;
      }

      BeginDrawing();
      ClearBackground(RAYWHITE);
      Settings_Draw(&settings);
      EndDrawing();
    } break;
    default:
      break;
    }

    framesCounter++;
  }
  Asteroid_DestroyManager(&asteroid_manager);
}
