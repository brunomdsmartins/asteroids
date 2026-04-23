#include <stdio.h>
#include <math.h>

#include "config.h"
#include "player.h"

/*
  ****************************************************************************** 
  *                           PRIVATE PLAYER FUNCTIONS                         *
  ****************************************************************************** 
*/

static void Player_SetType(Player *p, PlayerTypeEnum player_shape) {
  float player_length = 0.0f;
  float player_height = 0.0f;
  float player_radius = 0.0f;

  switch (player_shape) {
    case PLAYER_SQUARE:
      player_length = SCREEN_WIDTH / 20.0f;
      player_height = player_length;
      break;
    
    case PLAYER_TRIANGLE:
      player_length = SCREEN_WIDTH / 20.0f;
      player_height = (sqrtf(3.0f) / 2.0f) * player_length;
      break;

    case PLAYER_CIRCLE:
      player_radius = SCREEN_WIDTH / 50.0f;
      break;

    default:
      player_length = SCREEN_WIDTH / 20.0f;
      player_height = player_length;
      player_shape = PLAYER_SQUARE;
      break;
  }

  if(player_shape != PLAYER_CIRCLE) {
    p->type.shape = player_shape;
    p->type.length = player_length;
    p->type.height = player_height;
  } else {
    p->type.shape = player_shape;
    p->type.radius = player_radius;
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

  if (p->type.shape == PLAYER_CIRCLE) {
    left   = p->direction.x - p->type.radius;
    right  = p->direction.x + p->type.radius;
    top    = p->direction.y - p->type.radius;
    bottom = p->direction.y + p->type.radius;
  }
  else if (p->type.shape == PLAYER_TRIANGLE) {
    left   = p->direction.x - p->type.length / 2.0f;
    right  = p->direction.x + p->type.length / 2.0f;
    top    = p->direction.y - (2.0f/3.0f) * p->type.height;
    bottom = p->direction.y + (1.0f/3.0f) * p->type.height;
  }
  else {
    left   = p->direction.x - p->type.length / 2.0f;
    right  = p->direction.x + p->type.length / 2.0f;
    top    = p->direction.y - p->type.height / 2.0f;
    bottom = p->direction.y + p->type.height / 2.0f;
  }

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
  p->direction = (Vector2){(float)SCREEN_WIDTH / 2.0f, (float)SCREEN_HEIGHT / 2.0f};
  p->speed = (float)PLAYER_SPEED;
  Player_SetType(p, PLAYER_TRIANGLE);
}

void Player_Update(Player *p, float dt, Vector2 borders) {

  // Debug shapes
  // if (IsKeyDown(KEY_T)) {
  //   Player_SetType(p, p->type.shape == PLAYER_CIRCLE ? PLAYER_TRIANGLE : p->type.shape + 1);
  // }

  // Movimento
  Player_UpdateMovement(p, dt);

  // Limites
  Player_UpdateBorders(p, borders);
}

void Player_Draw(const Player *p) {
  switch (p->type.shape) {
  case PLAYER_SQUARE:
    DrawRectangle (
      p->direction.x - (p->type.length / 2),
      p->direction.y - (p->type.length / 2),
      p->type.length,
      p->type.height,
      RED
    );
    break;
  case PLAYER_TRIANGLE:
    DrawTriangle(
      (Vector2){p->direction.x, p->direction.y - (2.0f/3.0f) * p->type.height},
      (Vector2){p->direction.x - (p->type.length/2.0f), p->direction.y + (1.0f/3.0f) * p->type.height},
      (Vector2){p->direction.x + (p->type.length/2.0f), p->direction.y + (1.0f/3.0f) * p->type.height},
      RED
    );
    break;
  case PLAYER_CIRCLE:
    DrawCircleV(
      p->direction,
      p->type.radius,
      RED
    );
    break;
  default:
    break;
  }
};
