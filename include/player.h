#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>

#define PLAYER_MAX_SHAPE 3
#define PLAYER_BASE_SPEED 500.0f
#define PLAYER_BASE_HEALTH 1.0f
#define PLAYER_BASE_DAMAGE 1.0f
#define PLAYER_BASE_SCORE 0.0f

typedef enum { PLAYER_TRIANGLE, PLAYER_SQUARE, PLAYER_CIRCLE } PlayerTypeEnum;

typedef struct {
    float length;
    float height;
} PlayerGeometry;

typedef struct {
  PlayerGeometry geometry;
  PlayerTypeEnum shape;
  Color color;
} PlayerType;

typedef struct {
  Vector2 position;
  float speed;
} PlayerPhysics;

typedef struct {
  float health;
  float damage;
  float score;
} PlayerStats;

typedef struct {
  PlayerPhysics physics;
  PlayerType type;
  PlayerStats stats;
} Player;

void Player_Init(Player *p);
void Player_Update(Player *p, float dt, Vector2 borders);
void Player_Draw(const Player *p);
Vector2 Player_GetPosition(const Player *p);

#endif