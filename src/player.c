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
  if (IsKeyDown(KEY_K) || IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
    p->center.y -= p->speed * dt;
  }

  if (IsKeyDown(KEY_J) || IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
    p->center.y += p->speed * dt;
  }

  if (IsKeyDown(KEY_H) || IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
    p->center.x -= p->speed * dt;
  }

  if (IsKeyDown(KEY_L) || IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
    p->center.x += p->speed * dt;
  }
}

static void Player_UpdateBorders(Player *p, Vector2 borders) {
  float left, right, top, bottom;

  left = p->center.x - p->type.parameters.length / 2.0f;
  right = p->center.x + p->type.parameters.length / 2.0f;
  top = p->center.y - p->type.parameters.height / 2.0f;
  bottom = p->center.y + p->type.parameters.height / 2.0f;

  if (left < 0)
    p->center.x += -left;

  if (right > borders.x)
    p->center.x -= (right - borders.x);

  if (top < 0)
    p->center.y += -top;

  if (bottom > borders.y)
    p->center.y -= (bottom - borders.y);
}

/*
 ******************************************************************************
 *                           PUBLIC PLAYER FUNCTIONS                          *
 ******************************************************************************
 */

void Player_Init(Player *p) {
  p->center = (Vector2){(float)SCREEN_WIDTH / 2.0f, (float)SCREEN_HEIGHT / 2.0f};
  p->speed = (float)PLAYER_SPEED;
  p->type.shape = PLAYER_SQUARE;
  p->type.parameters.length = SCREEN_WIDTH / 20.0f;
  p->type.parameters.height = SCREEN_WIDTH / 20.0f;
}

void Player_Update(Player *p, float dt, Vector2 borders) {
  Player_UpdateShape(p);
  Player_UpdateMovement(p, dt);
  Player_UpdateBorders(p, borders);
}

void Player_Draw(const Player *p) {
  switch (p->type.shape) {
    case PLAYER_SQUARE:
      DrawRectangle(
        p->center.x - (p->type.parameters.length / 2),
        p->center.y - (p->type.parameters.length / 2),
        p->type.parameters.length, 
        p->type.parameters.height, 
        RED
      );
      break;
    case PLAYER_TRIANGLE:
      Vector2 top = {
          p->center.x,
          p->center.y - (p->type.parameters.height / 2.0f)
      };

      Vector2 left = {
          p->center.x - (p->type.parameters.length / 2.0f),
          p->center.y + (p->type.parameters.height / 2.0f)
      };

      Vector2 right = {
          p->center.x + (p->type.parameters.length / 2.0f),
          p->center.y + (p->type.parameters.height / 2.0f)
      };

      DrawTriangle(top, left, right, RED);
      break;
    case PLAYER_CIRCLE:
      DrawCircleV(p->center, (p->type.parameters.length / 2.0f), RED);
      break;
    default:
      break;
  }
};