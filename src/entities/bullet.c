#include "bullet.h"

#include <raylib.h>
#include <stdbool.h>

void Bullet_Init(Bullet *b) {
  b->size = 32.0f;
  b->alive = true;
}

void Bullet_Update(Bullet *b, float dt) {
  b->position.x += b->velocity.x * dt;
  b->position.y += b->velocity.y * dt;
}

void Bullet_Draw(const Bullet *b) { DrawCircleV(b->position, b->size, RED); }

Vector2 Bullet_GetPosition(const Bullet *b) { return b->position; }
