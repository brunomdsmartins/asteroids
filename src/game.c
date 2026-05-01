#include <raylib.h>

#include "config.h"

#include "game.h"
#include "menu.h"
#include "player.h"

void Game_Run(void) {
  GameState state = GAME_STATE_MENU;
  Player player;
  Menu menu;

  Player_Init(&player);

  while (!WindowShouldClose() && state != GAME_STATE_EXIT) {
    float dt = GetFrameTime();

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
      Player_Update(&player, dt, (Vector2){SCREEN_WIDTH, SCREEN_HEIGHT});

      BeginDrawing();

      DrawText("Press 'hjkl' to move", (float)SCREEN_WIDTH * 0.05,
               (float)SCREEN_HEIGHT * 0.05, 20, BLACK);

      ClearBackground(RAYWHITE);

      Player_Draw(&player);

      EndDrawing();
    } break;
    case GAME_STATE_SETTINGS: {
    } break;
    default:
      break;
    }
  }
}
