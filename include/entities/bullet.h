#ifndef BULLET_H
#define BULLET_H

#include <raylib.h>
#include <stdbool.h>

// #include "player.h"

#define BULLET_BASE_SPEED PLAYER_BASE_SPEED * 2.0f
#define BULLET_BASE_DAMAGE 1.0f

typedef struct {
  Vector2 position;
  Vector2 velocity;
  float size;
  bool alive;
} Bullet;

void Bullet_Init(Bullet *b);
void Bullet_Update(Bullet *b, float dt);
void Bullet_Draw(const Bullet *b);
Vector2 Bullet_GetPosition(const Bullet *b);

#endif
