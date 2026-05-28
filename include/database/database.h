#ifndef DATABASE_H
#define DATABASE_H

#include <stdbool.h>

#include "sqlite3.h"

typedef struct {
  sqlite3 *handle;
} Database;

bool DB_Open(Database *db);
void DB_Close(Database *db);

#endif
