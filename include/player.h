#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>

#define PLAYER_MAX_SHAPE 3

typedef enum { PLAYER_TRIANGLE, PLAYER_SQUARE, PLAYER_CIRCLE } PlayerTypeEnum;

typedef struct {
    float length;
    float height;
} PlayerParameters;

typedef struct {
  PlayerParameters parameters;
  PlayerTypeEnum shape;
} PlayerType;

typedef struct {
  Vector2 center;
  float speed;
  PlayerType type;
} Player;

void Player_Init(Player *p);
void Player_Update(Player *p, float dt, Vector2 borders);
void Player_Draw(const Player *p);

#endif