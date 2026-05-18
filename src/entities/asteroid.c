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
    pos.y = -a->geometry.radius;
    break;

  case 1: // Down
    pos.x = (float)GetRandomValue(0, SCREEN_WIDTH);
    pos.y = SCREEN_HEIGHT + a->geometry.radius;
    break;

  case 2: // Left
    pos.x = -a->geometry.radius;
    pos.y = (float)GetRandomValue(0, SCREEN_HEIGHT);
    break;

  default: // Right
    pos.x = SCREEN_WIDTH + a->geometry.radius;
    pos.y = (float)GetRandomValue(0, SCREEN_HEIGHT);
    break;
  }

  return pos;
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

  DrawCircleV(a->physics.position, a->geometry.radius, a->geometry.color);
}

AsteroidManager Asteroid_CreateManager(void) {
  // Start on 5 asteroids for capacity
  AsteroidManager m;
  m.capacity = 5;
  m.data = (Asteroid *)malloc(sizeof(Asteroid) * m.capacity);
  m.count = 0;
  return m;
}

void Asteroid_DestroyManager(AsteroidManager *m) {
  free(m->data);
  m->data = NULL;
  m->count = 0;
  m->capacity = 0;
}

void Asteroid_Remove(AsteroidManager *m, int index) {
  if (index < 0 || index >= m->count)
    return;

  m->data[index] = m->data[m->count - 1];
  m->count--;
}

bool Asteroid_IsOffScreen(Asteroid *a) {
  float radius = a->geometry.radius;

  return (a->physics.position.x < -radius ||
          a->physics.position.x > SCREEN_WIDTH + radius ||
          a->physics.position.y < -radius ||
          a->physics.position.y > SCREEN_HEIGHT + radius);
}

bool Asteroid_Add(AsteroidManager *m, Asteroid a) {
  if (m->count >= m->capacity) {

    int newCapacity = m->capacity * 2;

    Asteroid *newData = realloc(m->data, newCapacity * sizeof(Asteroid));

    if (!newData)
      return false;

    m->data = newData;
    m->capacity = newCapacity;
  }

  a.active = true;
  m->data[m->count] = a;
  m->count++;

  return true;
}

void Asteroid_UpdateAll(AsteroidManager *m, float dt) {
  for (int i = m->count - 1; i >= 0; i--) {
    Asteroid_Update(&m->data[i], dt);

    if (Asteroid_IsOffScreen(&m->data[i])) {
      Asteroid_Remove(m, i);
    }
  }
}

void Asteroid_DrawAll(AsteroidManager *m) {
  for (int i = 0; i < m->count; i++)
    Asteroid_Draw(&m->data[i]);
}

Asteroid Asteroid_GetRandomProfile() {
  Asteroid p = {0};

  p.geometry.size = (AsteroidSize)GetRandomValue(0, 2);

  switch (p.geometry.size) {

  case ASTEROID_SMALL:
    p.geometry.color = RED;
    p.geometry.radius = 12;
    p.physics.speed = 350;
    p.stats.health = 1;
    p.stats.damage = 1;
    p.stats.points = 25;
    break;

  case ASTEROID_MEDIUM:
    p.geometry.color = YELLOW;
    p.geometry.radius = 24;
    p.physics.speed = 250;
    p.stats.health = 1;
    p.stats.damage = 1;
    p.stats.points = 50;
    break;

  case ASTEROID_LARGE:
    p.geometry.color = GREEN;
    p.geometry.radius = 40;
    p.physics.speed = 150;
    p.stats.health = 1;
    p.stats.damage = 1;
    p.stats.points = 100;
    break;

  default:
    break;
  }

  return p;
}
