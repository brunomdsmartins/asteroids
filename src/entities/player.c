#include <math.h>

#include "config.h"
#include "player.h"

/*
 ******************************************************************************
 *                           PRIVATE PLAYER FUNCTIONS                         *
 ******************************************************************************
 */

static void Player_UpdateShape(Player *p) {
  if (IsKeyPressed(KEY_T)) {
    p->type.shape = (PlayerTypeEnum)((p->type.shape + 1) % PLAYER_MAX_SHAPE);
  }
}

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

  p->physics.position.x += dir.x * p->physics.speed * dt;
  p->physics.position.y += dir.y * p->physics.speed * dt;
}
static void Player_UpdateBorders(Player *p, Vector2 borders) {
  float halfW = p->type.geometry.length * 0.5f;
  float halfH = p->type.geometry.height * 0.5f;

  float left = p->physics.position.x - halfW;
  float right = p->physics.position.x + halfW;
  float top = p->physics.position.y - halfH;
  float bottom = p->physics.position.y + halfH;

  if (left < 0.0f)
    p->physics.position.x -= left;

  if (right > borders.x)
    p->physics.position.x -= (right - borders.x);

  if (top < 0.0f)
    p->physics.position.y -= top;

  if (bottom > borders.y)
    p->physics.position.y -= (bottom - borders.y);
}

/*
 ******************************************************************************
 *                           PUBLIC PLAYER FUNCTIONS                          *
 ******************************************************************************
 */

void Player_Init(Player *p) {
  p->physics.position =
      (Vector2){(float)HALF_SCREEN_WIDTH, (float)HALF_SCREEN_HEIGHT};
  p->physics.speed = (float)PLAYER_BASE_SPEED;

  p->type.color = RED;
  p->type.shape = PLAYER_SQUARE;
  p->type.geometry.length = (float)SCREEN_WIDTH / 20.0f;
  p->type.geometry.height = (float)SCREEN_WIDTH / 20.0f;

  p->stats.health = (float)PLAYER_BASE_HEALTH;
  p->stats.damage = (float)PLAYER_BASE_DAMAGE;
  p->stats.score = (float)PLAYER_BASE_SCORE;
}

void Player_Update(Player *p, float dt, Vector2 borders) {
  Player_UpdateShape(p);
  Player_UpdateMovement(p, dt);
  Player_UpdateBorders(p, borders);
}

void Player_Draw(const Player *p) {
  float halfW = p->type.geometry.length * 0.5f;
  float halfH = p->type.geometry.height * 0.5f;

  switch (p->type.shape) {
  case PLAYER_SQUARE:
    DrawRectangle((int)(p->physics.position.x - halfW),
                  (int)(p->physics.position.y - halfH),
                  (int)p->type.geometry.length, (int)p->type.geometry.height,
                  p->type.color);
    break;

  case PLAYER_TRIANGLE: {
    Vector2 top = {p->physics.position.x, p->physics.position.y - halfH};

    Vector2 left = {p->physics.position.x - halfW,
                    p->physics.position.y + halfH};

    Vector2 right = {p->physics.position.x + halfW,
                     p->physics.position.y + halfH};

    DrawTriangle(top, left, right, p->type.color);
  } break;

  case PLAYER_CIRCLE:
    DrawCircleV(p->physics.position, halfW, p->type.color);
    break;
  }
}

Vector2 Player_GetPosition(const Player *p) { return p->physics.position; }
