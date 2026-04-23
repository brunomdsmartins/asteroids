#ifndef player_h
#define player_h

#include <raylib.h>

typedef enum {
  PLAYER_TRIANGLE,
  PLAYER_SQUARE,
  PLAYER_CIRCLE
} PlayerTypeEnum;

typedef struct {
  union {
    struct {
      float length;
      float height;
    };
    float radius;
  };
  
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
