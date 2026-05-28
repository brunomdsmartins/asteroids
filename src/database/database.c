#include "database.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "sqlite3.h"

#ifdef _WIN32

#include <direct.h>

#define MKDIR(path) _mkdir(path)

#else

#include <sys/stat.h>

#define MKDIR(path) mkdir(path, 0755)

#endif

#define GAME_NAME "Asteroids"

static void DB_GetPath(char *out, size_t size) {
#ifdef _WIN32

  const char *appdata = getenv("APPDATA");
  snprintf(out, size, "%s\\%s", appdata, GAME_NAME);
  MKDIR(out);
  snprintf(out, size, "%s\\%s\\save.db", appdata, GAME_NAME);

#elif __APPLE__

  const char *home = getenv("HOME");
  snprintf(out, size, "%s/Library/Application Support/%s", home, GAME_NAME);
  MKDIR(out);
  snprintf(out, size, "%s/Library/Application Support/%s/save.db", home,
           GAME_NAME);

#else

  const char *home = getenv("HOME");
  snprintf(out, size, "%s/.config/%s", home, GAME_NAME);
  MKDIR(out);
  snprintf(out, size, "%s/.config/%s/save.db", home, GAME_NAME);

#endif
}

bool DB_Open(Database *db) {
  char path[512];

  DB_GetPath(path, sizeof(path));

  if (sqlite3_open(path, &db->handle) != SQLITE_OK) {
    printf("Failed to open database:\n%s\n", sqlite3_errmsg(db->handle));
    return false;
  }

  printf("Opened database:\n%s\n", path);

  return true;
}

void DB_Close(Database *db) {
  if (db->handle != NULL) {
    sqlite3_close(db->handle);
    db->handle = NULL;
  }
}
