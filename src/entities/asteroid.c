#include <math.h>
#include <raylib.h>
#include <stdlib.h>

#include "asteroid.h"
#include "config.h"

// PRIVATE ASTEROID FUNCTIONS

static Vector2 Asteroid_GetSpawnOutside(const Asteroid *a) {
  int side = GetRandomValue(0, 3);
  Vector2 pos = {0};

  switch (side) {
  case 0: // Top
    pos.x = (float)GetRandomValue(0, SCREEN_WIDTH);
    pos.y = -a->type.geometry.height;
    break;

  case 1: // Down
    pos.x = (float)GetRandomValue(0, SCREEN_WIDTH);
    pos.y = SCREEN_HEIGHT + a->type.geometry.height;
    break;

  case 2: // Right
    pos.x = -a->type.geometry.length;
    pos.y = (float)GetRandomValue(0, SCREEN_HEIGHT);
    break;

  default: // Right
    pos.x = SCREEN_WIDTH + a->type.geometry.length;
    pos.y = (float)GetRandomValue(0, SCREEN_HEIGHT);
    break;
  }

  return pos;
}

static void Asteroid_Init(Asteroid *a, Color color, AsteroidShape shape,
                          float length, float height, float speed, float health,
                          float damage, float points) {
  a->physics.position = (Vector2){0, 0};
  a->physics.velocity = (Vector2){0, 0};
  a->physics.speed = speed;

  a->type.color = color;
  a->type.shape = shape;
  a->type.geometry.length = length;
  a->type.geometry.height = height;

  a->stats.health = health;
  a->stats.damage = damage;
  a->stats.points = points;

  a->active = true;
}

// PUBLIC ASTEROID FUNCTIONS

void Asteroid_Spawn(Asteroid *a, Vector2 playerPos) {
  a->physics.position = Asteroid_GetSpawnOutside(a);

  Vector2 dir = {playerPos.x - a->physics.position.x,
                 playerPos.y - a->physics.position.y};

  float len = sqrtf(dir.x * dir.x + dir.y * dir.y);

  if (len > 0.0f) {
    dir.x /= len;
    dir.y /= len;
  }

  a->physics.velocity.x = dir.x * a->physics.speed;
  a->physics.velocity.y = dir.y * a->physics.speed;
}

void Asteroid_Update(Asteroid *a, float dt) {
  if (!a->active)
    return;

  a->physics.position.x += a->physics.velocity.x * dt;
  a->physics.position.y += a->physics.velocity.y * dt;
}

void Asteroid_Draw(const Asteroid *a) {
  if (!a->active)
    return;

  switch (a->type.shape) {
  case ASTEROID_SQUARE:
    DrawRectangle((int)(a->physics.position.x - a->type.geometry.length / 2.0f),
                  (int)(a->physics.position.y - a->type.geometry.height / 2.0f),
                  (int)a->type.geometry.length, (int)a->type.geometry.height,
                  a->type.color);
    break;

  case ASTEROID_TRIANGLE: {
    Vector2 top = {a->physics.position.x,
                   a->physics.position.y - a->type.geometry.height / 2.0f};

    Vector2 left = {a->physics.position.x - a->type.geometry.length / 2.0f,
                    a->physics.position.y + a->type.geometry.height / 2.0f};

    Vector2 right = {a->physics.position.x + a->type.geometry.length / 2.0f,
                     a->physics.position.y + a->type.geometry.height / 2.0f};

    DrawTriangle(top, left, right, a->type.color);
  } break;

  case ASTEROID_CIRCLE:
    DrawCircleV(a->physics.position, a->type.geometry.length / 2.0f,
                a->type.color);
    break;
  }
}

AsteroidManager Asteroid_CreateManager(void) {
  AsteroidManager m;
  m.data = (Asteroid *)malloc(sizeof(Asteroid) * 2);
  m.count = 0;
  m.capacity = 2;
  return m;
}

void Asteroid_DestroyManager(AsteroidManager *m) {
  free(m->data);
  m->data = NULL;
  m->count = 0;
  m->capacity = 0;
}

bool Asteroid_Add(AsteroidManager *m, Color color, AsteroidShape shape,
                  float length, float height, float speed, float health,
                  float damage, float points) {
  if (m->count >= m->capacity) {
    int newCapacity = m->capacity + 2;

    Asteroid *newData = realloc(m->data, newCapacity * sizeof(Asteroid));

    if (newData == NULL)
      return false;

    m->data = newData;
    m->capacity = newCapacity;
  }

  Asteroid_Init(&m->data[m->count], color, shape, length, height, speed, health,
                damage, points);

  m->count++;
  return true;
}

void Asteroid_UpdateAll(AsteroidManager *m, float dt) {
  for (int i = 0; i < m->count; i++)
    Asteroid_Update(&m->data[i], dt);
}

void Asteroid_DrawAll(AsteroidManager *m) {
  for (int i = 0; i < m->count; i++)
    Asteroid_Draw(&m->data[i]);
}
