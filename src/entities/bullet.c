#include "bullet.h"

#include <math.h>
#include <raylib.h>

void BulletManager_Init(BulletManager *m) {
  for (int i = 0; i < MAX_BULLETS; i++) {
    m->data[i].active = false;
    m->data[i].radius = 3.0f;
    m->data[i].damage = BULLET_BASE_DAMAGE;
  }
}

void BulletManager_Spawn(BulletManager *bm, Vector2 position, float rotation) {
  for (int i = 0; i < MAX_BULLETS; i++) {
    if (!bm->data[i].active) {
      bm->data[i].active = true;
      bm->data[i].position = position;

      float dirX = cosf(rotation - PI / 2.0f);
      float dirY = sinf(rotation - PI / 2.0f);

      bm->data[i].velocity.x = dirX * BULLET_BASE_SPEED;
      bm->data[i].velocity.y = dirY * BULLET_BASE_SPEED;

      bm->data[i].radius = 3.0f;
      bm->data[i].damage = BULLET_BASE_DAMAGE;
      return;
    }
  }
}

void BulletManager_Update(BulletManager *m, float dt, Vector2 borders) {
  for (int i = 0; i < MAX_BULLETS; i++) {
    Bullet *b = &m->data[i];
    if (!b->active)
      continue;

    b->position.x += b->velocity.x * dt;
    b->position.y += b->velocity.y * dt;

    if (b->position.x < 0 || b->position.x > borders.x || b->position.y < 0 ||
        b->position.y > borders.y) {
      b->active = false;
    }
  }
}

void BulletManager_Draw(const BulletManager *m) {
  for (int i = 0; i < MAX_BULLETS; i++) {
    if (!m->data[i].active)
      continue;

    DrawCircleV(m->data[i].position, m->data[i].radius, BLACK);
  }
}
