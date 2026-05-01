#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>

typedef struct {
  Vector2 position;
  float radius;
  float speed;
} Player;

void Player_Init(Player *p);
void Player_Update(Player *p, float dt, Vector2 borders);
void Player_Draw(const Player *p);

#endif
