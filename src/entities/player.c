#include <math.h>
#include <raylib.h>

#include "config.h"
#include "player.h"
#include "settings_menu.h"

// PRIVATE PLAYER FUNCTIONS

static void Player_UpdateMovement(Player *p, KeyboardLayout layout, float dt) {
  // Left, Bottom, Up, Right
  int keys[4];

  switch (layout) {
  case WASD:
    keys[0] = KEY_A;
    keys[1] = KEY_S;
    keys[2] = KEY_W;
    keys[3] = KEY_D;
    break;
  case ARROWS:
    keys[0] = KEY_LEFT;
    keys[1] = KEY_DOWN;
    keys[2] = KEY_UP;
    keys[3] = KEY_RIGHT;
    break;
  case VIM:
    keys[0] = KEY_H;
    keys[1] = KEY_J;
    keys[2] = KEY_K;
    keys[3] = KEY_L;
    break;
  default:
    break;
  }

  float rotation_speed = 5.0f;

  if (IsKeyDown(keys[0]))
    p->rotation -= rotation_speed * dt;

  if (IsKeyDown(keys[3]))
    p->rotation += rotation_speed * dt;

  Vector2 forward = {
      cosf(p->rotation - PI / 2.0f),
      sinf(p->rotation - PI / 2.0f),
  };

  if (IsKeyDown(keys[2])) {
    p->position.x += forward.x * p->speed * dt;
    p->position.y += forward.y * p->speed * dt;
  }
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

void Player_Update(Player *p, KeyboardLayout layout, float dt,
                   Vector2 borders) {
  Player_UpdateMovement(p, layout, dt);
  Player_UpdateBorders(p, borders);
}

void Player_Draw(const Player *p) {
  float size = (float)SCREEN_WIDTH / 20.0f;

  Vector2 local_top = {0.0f, -size * 0.5f};
  Vector2 local_left = {-size * 0.5f, size * 0.5f};
  Vector2 local_right = {size * 0.5f, size * 0.5f};

  float c = cosf(p->rotation);
  float s = sinf(p->rotation);

  Vector2 top = {
      p->position.x + local_top.x * c - local_top.y * s,
      p->position.y + local_top.x * s + local_top.y * c,
  };

  Vector2 left = {
      p->position.x + local_left.x * c - local_left.y * s,
      p->position.y + local_left.x * s + local_left.y * c,
  };

  Vector2 right = {
      p->position.x + local_right.x * c - local_right.y * s,
      p->position.y + local_right.x * s + local_right.y * c,
  };

  DrawTriangle(top, left, right, p->color);
}

Vector2 Player_GetPosition(const Player *p) { return p->position; }
