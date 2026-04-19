#include <stdio.h>

#include "config.h"

#include "player.h"

void Player_Init(Player *p) {
  p->position = (Vector2){(int)SCREEN_WIDTH / 2, (int)SCREEN_HEIGHT / 2};
  p->radius = (int)SCREEN_WIDTH / 50;
  p->speed = (float)PLAYER_SPEED;
};

void Player_Update(Player *p, float dt, Vector2 borders) {
  // Key movements
  if (IsKeyDown(KEY_H) || IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
    p->position.x -= p->speed * dt;
  }

  if (IsKeyDown(KEY_J) || IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
    p->position.y += p->speed * dt;
  }

  if (IsKeyDown(KEY_K) || IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
    p->position.y -= p->speed * dt;
  }

  if (IsKeyDown(KEY_L) || IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
    p->position.x += p->speed * dt;
  }

  // Screen borders
  if (p->position.x < p->radius) {
    p->position.x = p->radius;
  }

  if (p->position.x > borders.x - p->radius) {
    p->position.x = borders.x - p->radius;
  }

  if (p->position.y < p->radius) {
    p->position.y = p->radius;
  }

  if (p->position.y > borders.y - p->radius) {
    p->position.y = borders.y - p->radius;
  }
};

void Player_Draw(const Player *p) { DrawCircleV(p->position, p->radius, RED); };
