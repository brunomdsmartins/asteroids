#ifndef ASTEROID_H
#define ASTEROID_H

#include <raylib.h>

#define ASTEROID_MAX_SHAPE 3
#define ASTEROID_BASE_SPEED 500.0f
#define ASTEROID_BASE_HEALTH 1.0f
#define ASTEROID_BASE_DAMAGE 1.0f
#define ASTEROID_BASE_POINTS 0.0f

typedef enum {
  ASTEROID_SMALL,
  ASTEROID_MEDIUM,
  ASTEROID_LARGE,
} AsteroidSize;

typedef struct {
  float radius;
  AsteroidSize size;
  Color color;
} AsteroidGeometry;

typedef struct {
  Vector2 position;
  Vector2 velocity;
  float speed;
} AsteroidPhysics;

typedef struct {
  float health;
  float damage;
  float points;
} AsteroidStats;

typedef struct {
  AsteroidPhysics physics;
  AsteroidGeometry geometry;
  AsteroidStats stats;
  bool active;
} Asteroid;

typedef struct {
  Asteroid *data;
  int count;
  int capacity;
} AsteroidManager;

Asteroid Asteroid_GetRandomProfile();
void Asteroid_Spawn(Asteroid *a, Vector2 playerPos);
void Asteroid_Update(Asteroid *a, float dt);
void Asteroid_Draw(const Asteroid *a);
AsteroidManager Asteroid_CreateManager(void);
void Asteroid_DestroyManager(AsteroidManager *m);
bool Asteroid_Add(AsteroidManager *m, Asteroid a);
void Asteroid_UpdateAll(AsteroidManager *m, float dt);
void Asteroid_DrawAll(AsteroidManager *m);

#endif
