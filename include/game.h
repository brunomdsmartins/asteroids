#ifndef GAME_H
#define GAME_H

typedef enum {
  GAME_STATE_MENU,
  GAME_STATE_PLAYING,
  GAME_STATE_SETTINGS,
  GAME_STATE_PAUSE,
  GAME_STATE_EXIT
} GameState;

void Game_Run(void);

#endif
