#include <raylib.h>

#include "config.h"
#include "game.h"

int main(void) {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Asteroids");
  SetTargetFPS(60);

  Game_Run();

  CloseWindow();

  return 0;
}
