#include "database.h"
#include "highscores.h"

#include <sqlite3.h>
#include <stdbool.h>
#include <stdio.h>

bool Highscore_Init(Database *db) {
  const char *sql = "CREATE TABLE IF NOT EXISTS highscores ("
                    "id UUID PRIMARY KEY,"
                    "name TEXT NOT NULL,"
                    "score INTEGER NOT NULL"
                    ");";
  char *err = NULL;

  if (sqlite3_exec(db->handle, sql, NULL, NULL, &err) != SQLITE_OK) {
    printf("SQL Error:\n%s\n", err);
    sqlite3_free(err);
    return false;
  }

  return true;
}

bool Highscore_Add(Database *db, const char *name, int score) {
  sqlite3_stmt *stmt = NULL;

  const char *sql = "INSERT INTO highscores(name, score) "
                    "VALUES(?, ?);";

  if (sqlite3_prepare_v2(db->handle, sql, -1, &stmt, NULL) != SQLITE_OK) {
    return false;
  }

  sqlite3_bind_text(stmt, 1, name, -1, SQLITE_TRANSIENT);
  sqlite3_bind_int(stmt, 2, score);
  bool success = sqlite3_step(stmt) == SQLITE_DONE;
  sqlite3_finalize(stmt);

  return success;
}
