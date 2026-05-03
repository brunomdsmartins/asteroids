#include <math.h>
#include <raylib.h>

#include "config.h"
#include "player.h"

// PRIVATE PLAYER FUNCTIONS

static void Player_UpdateMovement(Player *p, float dt) {
  Vector2 dir = {0, 0};

  if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP) || IsKeyDown(KEY_K))
    dir.y -= 1.0f;

  if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_J))
    dir.y += 1.0f;

  if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_H))
    dir.x -= 1.0f;

  if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_L))
    dir.x += 1.0f;

  float len = sqrtf(dir.x * dir.x + dir.y * dir.y);

  if (len > 0.0f) {
    dir.x /= len;
    dir.y /= len;
  }

  p->position.x += dir.x * p->speed * dt;
  p->position.y += dir.y * p->speed * dt;
}

static void Player_UpdateBorders(Player *p, Vector2 borders) {
  float half_width = (float)SCREEN_WIDTH / 20.0f * 0.5f;

  float left = p->position.x - half_width;
  float right = p->position.x + half_width;
  float top = p->position.y - half_width;
  float bottom = p->position.y + half_width;

  if (left < 0.0f)
    p->position.x -= left;

  if (right > borders.x)
    p->position.x -= (right - borders.x);

  if (top < 0.0f)
    p->position.y -= top;

  if (bottom > borders.y)
    p->position.y -= (bottom - borders.y);
}

// PUBLIC PLAYER FUNCTIONS

void Player_Init(Player *p) {

  p->position =
      (Vector2){(float)(SCREEN_WIDTH / 2.0f), (float)(SCREEN_HEIGHT / 2.0f)};
  p->rotation = 0;
  p->color = RED;
  p->speed = (float)PLAYER_BASE_SPEED;
  p->stats.health = (float)PLAYER_BASE_HEALTH;
  p->stats.score = 0;
}

void Player_Update(Player *p, float dt, Vector2 borders) {
  Player_UpdateMovement(p, dt);
  Player_UpdateBorders(p, borders);
}

void Player_Draw(const Player *p) {
  float half_width = (float)SCREEN_WIDTH / 20.0f * 0.5f;

  Vector2 top = {p->position.x, p->position.y - half_width};

  Vector2 left = {p->position.x - half_width, p->position.y + half_width};

  Vector2 right = {p->position.x + half_width, p->position.y + half_width};

  DrawTriangle(top, left, right, p->color);
}

Vector2 Player_GetPosition(const Player *p) { return p->position; }
