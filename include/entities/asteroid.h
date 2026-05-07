#ifndef ASTEROID_H
#define ASTEROID_H

#include <raylib.h>

#define ASTEROID_MAX_SHAPE 3
#define ASTEROID_BASE_SPEED 500.0f
#define ASTEROID_BASE_HEALTH 1.0f
#define ASTEROID_BASE_DAMAGE 1.0f
#define ASTEROID_BASE_POINTS 0.0f

typedef enum {
  ASTEROID_TRIANGLE,
  ASTEROID_SQUARE,
  ASTEROID_CIRCLE
} AsteroidShape;

typedef struct {
  float length;
  float height;
} AsteroidGeometry;

typedef struct {
  AsteroidGeometry geometry;
  AsteroidShape shape;
  Color color;
} AsteroidType;

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
  AsteroidType type;
  AsteroidStats stats;
  bool active;
} Asteroid;

typedef struct {
  Asteroid *data;
  int count;
  int capacity;
} AsteroidManager;

void Asteroid_Spawn(Asteroid *a, Vector2 playerPos);
void Asteroid_Update(Asteroid *a, float dt);
void Asteroid_Draw(const Asteroid *a);
AsteroidManager Asteroid_CreateManager(void);
void Asteroid_DestroyManager(AsteroidManager *m);
bool Asteroid_Add(AsteroidManager *m, Color color, AsteroidShape shape,
                  float length, float height, float speed, float health,
                  float damage, float points);
void Asteroid_UpdateAll(AsteroidManager *m, float dt);
void Asteroid_DrawAll(AsteroidManager *m);

#endif
