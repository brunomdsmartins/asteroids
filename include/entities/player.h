#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>

#define PLAYER_BASE_SPEED 500.0f
#define PLAYER_BASE_HEALTH 1.0f

typedef struct {
  float health;
  float score;
} PlayerStats;

typedef struct {
  Vector2 position;
  float rotation;
  Color color;
  float speed;
  PlayerStats stats;
} Player;

void Player_Init(Player *p);
void Player_Update(Player *p, float dt, Vector2 borders);
void Player_Draw(const Player *p);
Vector2 Player_GetPosition(const Player *p);

#endif
