#ifndef BULLET_H
#define BULLET_H

#include <raylib.h>
#include <stdbool.h>

#define BULLET_BASE_SPEED 900.0f
#define BULLET_BASE_DAMAGE 1.0f
#define MAX_BULLETS 32

typedef struct {
  Vector2 position;
  Vector2 velocity;
  float radius;
  float damage;
  bool active;
} Bullet;

typedef struct {
  Bullet data[MAX_BULLETS];
} BulletManager;

void BulletManager_Init(BulletManager *m);
void BulletManager_Spawn(BulletManager *m, Vector2 position, float rotation);
void BulletManager_Update(BulletManager *m, float dt, Vector2 borders);
void BulletManager_Draw(const BulletManager *m);

#endif
