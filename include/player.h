#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>

typedef enum { PLAYER_TRIANGLE, PLAYER_SQUARE, PLAYER_CIRCLE } PlayerTypeEnum;

typedef union {
  struct {
    float length;
    float height;
  };
  float radius;
} PlayerParameters;

typedef struct {
  PlayerParameters parameters;
  PlayerTypeEnum shape;
} PlayerType;

typedef struct {
  Vector2 direction;
  float speed;
  PlayerType type;
} Player;

void Player_Init(Player *p);
void Player_Update(Player *p, float dt, Vector2 borders);
void Player_Draw(const Player *p);

#endif
