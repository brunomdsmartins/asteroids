#ifndef HIGHSCORES_H
#define HIGHSCORES_H

#include <stdbool.h>

#include "database.h"

typedef struct {
  char name[32];
  int score;
} Highscore;

bool Highscore_Init(Database *db);
bool Highscore_Add(Database *db, const char *name, int score);

#endif
