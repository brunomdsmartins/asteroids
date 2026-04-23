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
    switch (p->type.shape) {
    case PLAYER_CIRCLE:
      p->type.shape = PLAYER_TRIANGLE;
      break;
    case PLAYER_TRIANGLE:
      p->type.shape = PLAYER_SQUARE;
      break;
    case PLAYER_SQUARE:
      p->type.shape = PLAYER_CIRCLE;
      break;
    default:
      break;
    }
  }
}

static void Player_UpdateMovement(Player *p, float dt) {
  if (IsKeyDown(KEY_K) || IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
    p->direction.y -= p->speed * dt;
  }

  if (IsKeyDown(KEY_J) || IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
    p->direction.y += p->speed * dt;
  }

  if (IsKeyDown(KEY_H) || IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
    p->direction.x -= p->speed * dt;
  }

  if (IsKeyDown(KEY_L) || IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
    p->direction.x += p->speed * dt;
  }
}

static void Player_UpdateBorders(Player *p, Vector2 borders) {
  float left, right, top, bottom;

  switch (p->type.shape) {
  case PLAYER_CIRCLE:
    left = p->direction.x - p->type.parameters.radius;
    right = p->direction.x + p->type.parameters.radius;
    top = p->direction.y - p->type.parameters.radius;
    bottom = p->direction.y + p->type.parameters.radius;
    break;

  case PLAYER_TRIANGLE:
    left = p->direction.x - p->type.parameters.length / 2.0f;
    right = p->direction.x + p->type.parameters.length / 2.0f;
    top = p->direction.y - (2.0f / 3.0f) * p->type.parameters.height;
    bottom = p->direction.y + (1.0f / 3.0f) * p->type.parameters.height;
    break;

  default:
    left = p->direction.x - p->type.parameters.length / 2.0f;
    right = p->direction.x + p->type.parameters.length / 2.0f;
    top = p->direction.y - p->type.parameters.height / 2.0f;
    bottom = p->direction.y + p->type.parameters.height / 2.0f;
    break;
  };

  if (left < 0)
    p->direction.x += -left;

  if (right > borders.x)
    p->direction.x -= (right - borders.x);

  if (top < 0)
    p->direction.y += -top;

  if (bottom > borders.y)
    p->direction.y -= (bottom - borders.y);
}

/*
 ******************************************************************************
 *                           PUBLIC PLAYER FUNCTIONS                          *
 ******************************************************************************
 */

void Player_Init(Player *p) {
  p->direction =
      (Vector2){(float)SCREEN_WIDTH / 2.0f, (float)SCREEN_HEIGHT / 2.0f};
  p->speed = (float)PLAYER_SPEED;
  p->type.shape = PLAYER_TRIANGLE;
}

void Player_Update(Player *p, float dt, Vector2 borders) {
  Player_UpdateShape(p);
  Player_UpdateMovement(p, dt);
  Player_UpdateBorders(p, borders);
}

void Player_Draw(const Player *p) {
  switch (p->type.shape) {
  case PLAYER_SQUARE:
    DrawRectangle(p->direction.x - (p->type.parameters.length / 2),
                  p->direction.y - (p->type.parameters.length / 2),
                  p->type.parameters.length, p->type.parameters.height, RED);
    break;
  case PLAYER_TRIANGLE:
    DrawTriangle(
        // Nariz da cena
        (Vector2){p->direction.x,
                  p->direction.y + (p->type.parameters.height / 2)},
        // Esquerdo da cena
        (Vector2){p->direction.x - (p->type.parameters.length / 2.0f),
                  p->direction.y - (p->type.parameters.length / 2.0f)},
        // Direito da cena
        (Vector2){p->direction.x + (p->type.parameters.length / 2.0f),
                  p->direction.y - (p->type.parameters.length / 2.0f)},
        RED);
    break;
  case PLAYER_CIRCLE:
    DrawCircleV(p->direction, (p->type.parameters.length / 2.0f), RED);
    break;
  default:
    break;
  }
};
